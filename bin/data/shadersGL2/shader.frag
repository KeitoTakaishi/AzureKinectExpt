#version 120
// this is how we receive the texture
uniform sampler2D tex0;
varying vec2 texCoordVarying;

void main()
{
    vec2 uv = gl_TexCoord[0].xy;
    uv.y *= -1.0;
    vec4 c = texture2D(tex0, uv);

    //gl_FragColor = c;
    float coef = 280.0;
    float col = c.r * coef;
    gl_FragColor = vec4(vec3(col), 1.0) + vec4(0.3, 0.3,0.3,0.0);
}
