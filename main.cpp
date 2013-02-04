
#include "FORZE.h"

using namespace FORZE;

#define NUMBER 16


class ElectricField : public Layer {
    
    LayerColor *layerColor_;
    
    
public:
    ElectricField()
    {
        setTrackedEvents(kFZEventType_Tap);
        schedule();
        
        // CREATE AUTHOR LABEL
        const char *text =
        "Manuel Martinez-Almeida\n"
        "Universidad de Valladolid. Physics, Electric potential.\n\n"
        "White: equipotential lines\n"
        "Green: positive potential\n"
        "Red: negative potential\n"
        "Blue: potential close to zero";
        Label *textLa = new Label(text, "helvetica.fnt");
        textLa->setAnchorPoint(0, 1);
        textLa->setScale(0.8f);
        textLa->setPosition(10, FZ_CANVAS_SIZE().height-20);
        textLa->setColor(fzWHITE * 0.9f);
        addChild(textLa, 100);
        
        
        
        // FORZE2D logo
        Sprite *sprite = new Sprite("logo_forze.png");
        sprite->setPosition(getContentSize()/2);
        sprite->runAction(new Sequence(new DelayTime(1),
                                       new FadeOut(2),
                                       new CallFunc(sprite, SEL_VOID(Node::removeFromParent)), NULL));
        
        addChild(sprite, 100);
        
        // CREATE A LAYER COLOR
        // This label will be the opengl polygon where the shader will be applied
        layerColor_ = new LayerColor(fzWHITE);
        addChild(layerColor_);
        
        try
        {
            // LOAD GLSL SHADER
            GLProgram *program = new GLProgram("simulation.vert", "simulation.frag");
            program->addGenericAttributes();
            program->link();
            layerColor_->setGLProgram(program);
            
        } catch(std::exception& e) {
            FZLog("Failed.");
        }
        
        
        // MENU
        MenuItem *item1 = new MenuItemLabel("Add +", "helvetica.fnt",
                                            this, SEL_PTR(ElectricField::dropPositive));
        MenuItem *item2 = new MenuItemLabel("Add -", "helvetica.fnt",
                                            this, SEL_PTR(ElectricField::dropNegative));
        MenuItem *item3 = new MenuItemLabel("Remove", "helvetica.fnt",
                                            this, SEL_PTR(ElectricField::removeLastOne));
        MenuItem *item4 = new MenuItemLabel("Condenser", "helvetica.fnt",
                                            this, SEL_PTR(ElectricField::condenser));
        MenuItem *item5 = new MenuItemLabel("Circle", "helvetica.fnt",
                                            this, SEL_PTR(ElectricField::circle));
        
        Menu *menu = new Menu(item1, item2, item3, item4, item5, NULL);
        menu->alignChildrenHorizontally(50);
        menu->setPosition(getContentSize().width/2, 40);
        addChild(menu);
    }
    
    
    void createChange(const fzPoint& pos, int chargeValue)
    {
        if(layerColor_->getChildren().size() < NUMBER) {
            
            Node *charge = new Node();
            charge->setPosition(pos);
            charge->setTag(chargeValue);
            layerColor_->addChild(charge);
        }
    }
    
    
    void dropPositive(void*)
    {
        createChange(fzPoint(40, getContentSize().height/2), 250);
    }
    
    void dropNegative(void*)
    {
        createChange(fzPoint(getContentSize().width-40, getContentSize().height/2), -250);
    }
    
    
    void circle(void*)
    {
        layerColor_->removeAllChildren();
        
        fzPoint center = getContentSize()/2;
        for(int i = 0; i < 15; ++i)
        {
            float angle = i*M_PI*2/15;
            fzPoint pos = center + fzPoint(cosf(angle)*250, sinf(angle)*250);
            createChange(pos, 110);
        }
    }
    
    
    void condenser(void*)
    {
        layerColor_->removeAllChildren();

        fzPoint center = getContentSize()/2;
        for(int i = 0; i < 7; ++i)
            createChange(center + fzPoint(-100, 200-i*70), 250);
            
        for(int i = 0; i < 7; ++i)
            createChange(center + fzPoint(100, 200-i*70), -250);
    }
    
    
    void removeLastOne(void*)
    {
        layerColor_->removeChild((Node*)layerColor_->getChildren().back());
    }
    
    
    void update(fzFloat)
    {
        Node *node;
        GLfloat values[NUMBER*3];
        
        fzPoint rate = Director::Instance().getViewPort();
        rate = rate.compMult(1/getContentSize());
        
        
        GLint i = 0;
        FZ_LIST_FOREACH(layerColor_->getChildren(), node)
        {
            values[i*3 + 0] = node->getPosition().x * rate.x;
            values[i*3 + 1] = node->getPosition().y * rate.y;
            values[i*3 + 2] = node->getTag() * rate.x;
            ++i;
        }
        
        layerColor_->getGLProgram()->setUniform1i("u_number", i);
        layerColor_->getGLProgram()->setUniform3fv("u_data[0]", i, values);
    }
    
    
    bool event(Event& event)
    {
        switch (event.getState()) {
            case kFZEventState_Began:
            {
                Node *charge;
                FZ_LIST_FOREACH(layerColor_->getChildren(), charge) {
                    if(charge->getPosition().distance(event.getPoint()) < 80.0f) {
                        event.setUserData(charge);
                        return true;
                    }
                }
                return false;
            }
            default:
            {
                Light *light = static_cast<Light*>(event.getUserData());
                if(light)
                    light->setPosition(event.getPoint());
                
                return false;
            }
        }
    }
};


// APPLICATION DELEGATE
// A instance of this object will receive the application events
// through the ApplicationProtocol protocol
class AppDelegate : public AppDelegateProtocol {
public:
    AppDelegate() {}
    
    virtual GLConfig fzGLConfig()
    {
        GLConfig config;
        config.quality = 1.0f;
        return config;
    }
    
    // this method is called when the application launched.
    void applicationLaunched(void *options)
    {
        ElectricField *layer = new ElectricField();
        
        Scene *scene = new Scene();
        scene->addChild(layer);
        Director::Instance().pushScene(scene);
        
        new Console();
    }
};


// APPLICATION'S ENTRY POINT
int main(int argc, char *argv[])
{
    FORZE_INIT(new AppDelegate(), kFZSize_Auto, argc, argv);
    return EXIT_SUCCESS;
}


