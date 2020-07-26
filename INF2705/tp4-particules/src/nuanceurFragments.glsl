#version 410

uniform sampler2D laTexture;
uniform int texnumero;

in Attribs {
   vec4 couleur;
   vec2 texCoord;
} AttribsIn;

out vec4 FragColor;

void main( void )
{
   // Mettre un test bidon afin que l'optimisation du compilateur n'élimine l'attribut "couleur".
   // Vous MODIFIEREZ ce test inutile!


   if(texnumero > 0){
       vec4 texCoul = texture( laTexture, AttribsIn.texCoord );
       if ( texCoul.a <= 0.1 ) discard;
       FragColor = vec4(mix(AttribsIn.couleur.rgb, texCoul.rgb, 0.6),AttribsIn.couleur.a);
   }
   else{
       FragColor = AttribsIn.couleur;
   }
}
