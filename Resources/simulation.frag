
#define MAX_NUMBER_ITEMS 16
#define BACKGROUND_COLOR vec3(0, 0, 0.2)
#define ZERO_COLOR vec3(0, 0, 0.5)
#define POSITIVE_COLOR vec3(0, 1, 0)
#define NEGATIVE_COLOR vec3(1, 0, 0)
#define VECTOR_COLOR vec3(1, 0.8, 0)
#define LINE_COLOR vec3(1, 1, 1)
#define BOX vec2(50, 50)
#define RANGE 0.05

#ifdef GL_ES
precision highp float;
uniform highp vec3 u_data[MAX_NUMBER_ITEMS];
uniform highp int u_number;

#else
uniform vec3 u_data[MAX_NUMBER_ITEMS];
uniform int u_number;

#endif


bool isClose(float value, float center, float radius)
{
    return (value > (center-radius) && value < (center+radius));
}

void main()
{
    // We reset the field vector, zero, zero.
    vec2 vectorFinal = vec2(0);
    vec3 color;
    // We reset the potential, zero.
    float value = 0.0;
    // here, we iterate the electric charges stored in u_data where
    // u_data.xy is the position vector.
    // u_data.z is the change value in coulombs.
    for(int i = 0; i < MAX_NUMBER_ITEMS; ++i)
    {
        if(i < u_number) {
            // Vector from charge to pixel coord (current position).
            vec2 vector = gl_FragCoord.xy - u_data[i].xy;
            
            // Vector length -> distance
            float dist = inversesqrt(vector.x*vector.x+vector.y*vector.y);
            
            // Compute potencial:  q/d
            float potential = u_data[i].z * dist;
            
            // Compute vector: v * q /(d^3) = v * p / d^2
            vectorFinal += vector * (potential*dist);
            value += potential;
        }
    }
    
    if(isClose(value, 0.0, RANGE))
        // If potential is close to zero: render blue
        color = ZERO_COLOR;
    
    else if(isClose(value, ceil(value), RANGE))
        // If potential is close to the integer part: render white (equipotential line)
        color = LINE_COLOR;
    
    else
    {
        value *= 0.1;
        
        // If the potencial is positive we render in green (mix ~= blending)
        if(value > 0.0)
        		color = mix(BACKGROUND_COLOR, POSITIVE_COLOR, min(value, 1.0));
        
        // If the potencial is negative we render in green (mix ~= blending)
        else
        		color = mix(BACKGROUND_COLOR, NEGATIVE_COLOR, min(-value, 1.0));
    }
    
    
    
    // normalize final vector
    // In order to render the arrows.
    // 1. We move to a relative system : mod(gl_FragCoord.xy, BOX)
    // 2. Get vector from the center of the system to the relative point: p - (BOX/2)
    // 3. Normalize vector
    // 4. Change the sign.
    // If the dot product of the relative vector and the vector final is close to 1
    // this means that we are in a pixel that is part of an arrow.
    value = length(vectorFinal);
    if(value > 0.14) {
        vec2 relative = -normalize(mod(gl_FragCoord.xy, BOX) - (BOX*0.5));
        
        vectorFinal /= value;
        if(isClose(dot(relative, vectorFinal), 1.0, 0.006))
            color = mix(color, VECTOR_COLOR, min(value*0.7, 1.0));

    }
    
    gl_FragColor = vec4(color, 1);
}
