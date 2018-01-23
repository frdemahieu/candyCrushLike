#include "Util.h"


ref_ptr<Text> Util::creerEtPlacerOsgText(string txt, double x, double y,double z, double taillePolice){

	ref_ptr<Font> maPolice = readFontFile("arial.ttf");
	ref_ptr<Text> osgTxt = new osgText::Text;
	osgTxt->setFont(maPolice);
	osgTxt->setCharacterSize(taillePolice); 
	osgTxt->setColor(Vec4(0.93f,0.92f,0.79f,1.0f));
	osgTxt->setPosition(Vec3(x,y,z)); 
	osgTxt->setText(txt);

	return osgTxt;
}

string Util::IntToString(int nbr){
	string mot;
	stringstream out;
	out << nbr;
	mot = out.str();
	return mot;
}

ref_ptr<StateSet> Util::getTexture2D(string imgName, ref_ptr<StateSet> state) {

	ref_ptr<Texture2D> texture = new Texture2D;

	texture->setDataVariance(Object::DYNAMIC);
	texture->setFilter(Texture::MIN_FILTER, Texture::LINEAR_MIPMAP_LINEAR);
	texture->setFilter(Texture::MAG_FILTER, Texture::LINEAR);

   // charge une image par la lecture d'un fichier
   ref_ptr<Image> image = osgDB::readImageFile(imgName);
   if (!image)
   {
      cout << " couldn't find texture, quiting." << endl;
      return NULL;
   }

   // Assigne la texture que nous avons lue depuis le fichier: 
   texture->setImage(image);
   texture->setWrap(Texture::WRAP_S, Texture::REPEAT);
   texture->setWrap(Texture::WRAP_T, Texture::REPEAT);
   
   if(state == NULL) {
	// Crée un nouveau StateSet avec les options par défaut: 
	state = new StateSet();
   }
  

	// Assigne notre texture à la texture 0 de notre StateSet
	state->setTextureAttributeAndModes(0,texture,StateAttribute::ON);
	state->setMode(GL_LIGHTING,StateAttribute::ON);
	//Permet de mettre la texture sur toutes les faces du cube.
	TexEnv* decalTexEnv = new TexEnv();
	decalTexEnv->setMode(TexEnv::DECAL);
	state->setTextureAttribute(0,decalTexEnv,StateAttribute::ON);

	state->setMode(GL_LIGHTING,StateAttribute::OFF);
	  
   return state;
}