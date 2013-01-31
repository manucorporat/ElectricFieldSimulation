
#include "FORZE.h"

using namespace FORZE;

#define NUMBER 15


class ElectricField : public Layer {
    
    LayerColor *layerColor_;
    
    
public:
    ElectricField()
    {
        setTrackedEvents(kFZEventType_Tap);
        
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
        
        {
            // CREATE A LAYER COLOR
            // This label will be the opengl polygon where the shader will be applied
            layerColor_ = new LayerColor(fzWHITE);
            addChild(layerColor_);
            
            
            // LOAD GLSL SHADER
            GLProgram *program = new GLProgram("simulation.vert", "simulation.frag");
            program->addGenericAttributes();
            program->link();
            layerColor_->setGLProgram(program);
        }
        
        
        // ITEM
        MenuItemImage *item = new MenuItemImage("menu_reset.png", this, SEL_PTR(ElectricField::removeLastOne));
        item->setPosition(30, 20);
        item->setScale(0.5f);
        addChild(item, 100);
        
        
        // SCHEDULE UPDATE()
        schedule();
    }
    
    
    void removeLastOne(void*sender)
    {
        layerColor_->removeChild((Node*)layerColor_->getChildren().back());
    }
    
    
    void createCharge(const fzPoint& pos)
    {
        if(layerColor_->getChildren().size() < NUMBER) {
            
            float chargeValue = 250;
            if(FZ_RANDOM_0_1() < 0.5)
                chargeValue = -chargeValue;
            
            LayerColor *charge = new LayerColor(fzRED, fzSize(1, 1));
            charge->setPosition(pos);
            charge->setTag(chargeValue);
            layerColor_->addChild(charge);
        }
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
                createCharge(event.getPoint());
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
    FORZE_INIT(new AppDelegate(), kFZSize_iPadLandscape, argc, argv);
    return EXIT_SUCCESS;
}


