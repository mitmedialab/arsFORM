#extension GL_ARB_texture_rectangle : enable
varying float depth;


void main()

{
	gl_FragColor = vec4(depth, depth, depth, 1.0);
    //gl_FragColor = vec4(1.0, 0, 0, 1.0);
}



