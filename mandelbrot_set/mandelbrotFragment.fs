#version 410

out vec4 colorOut;
uniform double screen_ratio;
uniform dvec2 screen_size;
uniform dvec2 center;
uniform double zoom;
uniform int itr;
uniform int exponent;


vec4 map_to_color(float t)
{
    float r = 9.0 * (1.0 - t) * t * t * t;
    float g = 15.0 * (1.0 - t) * (1.0 - t) * t * t;
    float b = 8.5 * (1.0 - t) * (1.0 - t) * (1.0 - t) * t;

    return vec4(r, g, b, 1.0);
}


void main()
{
    dvec2 z, c;
    c.x = screen_ratio * (gl_FragCoord.x / screen_size.x - 0.5);
    c.y = (gl_FragCoord.y / screen_size.y - 0.5);

    c.x = c.x / zoom;
    c.y = c.y / zoom;

    c.x = center.x + c.x;
    c.y = center.y + c.y;

    int i;
    for(i = 0; i < itr; i++) {
        float z_x = float(z.x);
        float z_y = float(z.y);
        double x_temp = pow((z_x * z_x) + (z_y * z_y), float(exponent*0.5)) * cos(exponent*atan(z_y,z_x)) + c.x;
        double y_temp = pow((z_x * z_x) + (z_y * z_y), float(exponent*0.5)) * sin(exponent*atan(z_y,z_x)) + c.y;
        double x = x_temp;



   	    if((x * x + y_temp * y_temp) > 4.0) break;
   		    z.x = x;
   		    z.y = y_temp;
    }

    float t = float(i) / float(itr);

    colorOut = map_to_color(t);
   }