
#define MAX_NUMBER_ITEMS 15
#define BACKGROUND_COLOR vec4(0, 0, 0.2, 1)
#define ZERO_COLOR vec4(0, 0, 0.5, 1)
#define POSITIVE_COLOR vec4(0, 1, 0, 1)
#define NEGATIVE_COLOR vec4(1, 0, 0, 1)
#define VECTOR_COLOR vec4(1, 0.8, 0, 1)
#define LINE_COLOR vec4(1, 1, 1, 1)
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
    vec2 vectorFinal = vec2(0.0);
    
    // We reset the potential, zero.
    float potentialFinal = 0.0;
    
    // here, we iterate the electric charges stored in u_data where
    // u_data.xy is the position vector.
    // u_data.z is the change value in coulombs.
    for(int i = 0; i < MAX_NUMBER_ITEMS; ++i)
    {
        if(i < u_number) {
            // Vector from charge to pixel coord (current position).
            vec2 vector = gl_FragCoord.xy - u_data[i].xy;
            
            // Vector length -> distance
            float dist = length(vector);
            
            // Compute potencial:  q/d
            float potential = u_data[i].z / dist;
            
            // Compute vector: v * q /(d^3) = v * p / d^2
            vectorFinal += vector * (potential/(dist*dist));
            potentialFinal += potential;
        }
    }
    
    // normalize final vector
    float module = length(vectorFinal);
    vectorFinal /= module;
    
    // In order to render the arrows.
    // 1. We move to a relative system : mod(gl_FragCoord.xy, BOX)
    // 2. Get vector from the center of the system to the relative point: p - (BOX/2)
    // 3. Normalize vector
    // 4. Change the sign.
    vec2 relative = -normalize(mod(gl_FragCoord.xy, BOX) - (BOX/2.0));

    // If the dot product of the relative vector and the vector final is close to 1
    // this means that we are in a pixel that is part of an arrow.
    if(isClose(dot(relative, vectorFinal), 1.0, 0.003) && module > 0.00001)
        gl_FragColor = VECTOR_COLOR;
    
    else
    {
        if(isClose(potentialFinal, 0.0, RANGE))
            // If potential is close to zero: render blue
            gl_FragColor = ZERO_COLOR;
        
        else if(isClose(potentialFinal, floor(potentialFinal), RANGE))
            // If potential is close to the integer part: render white (equipotential line)
            gl_FragColor = LINE_COLOR;
        
        else
        {
            potentialFinal = clamp(potentialFinal / 10.0, -1.0, 1.0);
            
            // If the potencial is positive we render in green (mix ~= blending)
            if(potentialFinal > 0.0)
                gl_FragColor = mix(BACKGROUND_COLOR, POSITIVE_COLOR, potentialFinal);
            
            // If the potencial is negative we render in green (mix ~= blending)
            else
                gl_FragColor = mix(BACKGROUND_COLOR, NEGATIVE_COLOR, -potentialFinal);
        }
    }
}
