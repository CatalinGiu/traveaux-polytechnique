#version 410

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;
in Attribs {
   vec4 couleur;
   float tempsDeVieRestant;
   float sens; // du vol
} AttribsIn[];

out Attribs {
   vec4 couleur;
   vec2 texCoord;
} AttribsOut;

uniform int texnumero;
uniform float dt;

void main()
{
   vec2 coins[4];
   if(texnumero == 0){
       coins[0] = vec2( -0.1,  0.1 );
       coins[1] = vec2( -0.1, -0.1 );
       coins[2] = vec2(  0.1,  0.1 );
       coins[3] = vec2(  0.1, -0.1 );
   }
   else{
        coins[0] = vec2( -0.5,  0.5 );
        coins[1] = vec2( -0.5, -0.5 );
        coins[2] = vec2(  0.5,  0.5 );
        coins[3] = vec2(  0.5, -0.5 );
   }
   for ( int i = 0 ; i < 4 ; ++i )
   {
      if(texnumero == 1){
            mat2 Rotation = mat2( cos(4 * AttribsIn[0].tempsDeVieRestant), sin(4 * AttribsIn[0].tempsDeVieRestant),
                                   -sin(4 *AttribsIn[0].tempsDeVieRestant), cos(4 * AttribsIn[0].tempsDeVieRestant)
                                   );
            coins[i] = Rotation * coins[i];
            if( i == 0){
                AttribsOut.texCoord = vec2(0, 1);
            }
            else if( i == 1){
                AttribsOut.texCoord = vec2(0, 0);
            }
            else if( i == 2){
                AttribsOut.texCoord = vec2(1, 1);
            }
            else if( i == 3){
                AttribsOut.texCoord = vec2(1, 0);
            }
      }
      float pointsize = 2;
      float fact = 0.025 * pointsize;
      vec2 decalage = coins[i]; // on positionne successivement aux quatre coins
      vec4 pos = vec4( gl_in[0].gl_Position.xy + fact * decalage, gl_in[0].gl_Position.zw );

      gl_Position = pos;    // on termine la transformation débutée dans le nuanceur de sommets

      AttribsOut.couleur = AttribsIn[0].couleur;

      if(texnumero == 2){
            int modulo = int ( mod ( ( AttribsIn[0].tempsDeVieRestant * 20 ), 16));
            if(
             ( ( i == 2 || i == 3) && AttribsIn[0].sens > 0) ||
             ( ( i == 0 || i == 1) && AttribsIn[0].sens < 0) ) {
                AttribsOut.texCoord = vec2(modulo / 16.0 + 1.0/16.0 , coins[i].y + 0.5);
                }
            else{
                AttribsOut.texCoord = vec2(modulo / 16.0, coins[i].y + 0.5);
            }
      }
      else if(texnumero == 3){
                  int modulo = int ( mod ( ( AttribsIn[0].tempsDeVieRestant * 4 ), 16));
                  if(i == 2 || i == 3){
                      AttribsOut.texCoord = vec2(modulo / 16.0 + 1.0/16.0 , coins[i].y + 0.5);
                      }
                  else{
                      AttribsOut.texCoord = vec2(modulo / 16.0, coins[i].y + 0.5);
                  }
            }
      EmitVertex();
   }

}
