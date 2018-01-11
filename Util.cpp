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
      cout << "Impossible de charger la texture" << endl;
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


   return state;
}
//fonction qui parse un fichier qui contient tous les points des formes personnalisées
//Syntaxe qui ressemble au fichier OBJ mais simplifié ( il y a des commentaires dans les fichier .object" pour expliquer la syntaxe )
Geometry* Util::chargerFichier(string stringFichier,string texture){
	Geometry* formeBizarreVertices= new osg::Geometry();
	
	fstream fichier(stringFichier.c_str());

	if(!fichier){
		cout << "Impossible d'ouvrir le fichier !\n";
	}
	Vec3Array* vertices = new Vec3Array;
	Vec2Array* texcoords = new Vec2Array(30);
	osg::Vec3Array* normal = new Vec3Array(30);
	int nbrTexture = 0;
	int nbrNormal = 0;
	while(!fichier.eof()){
		
		char type;
		fichier >> type;
		float coord[3];
		
		if(type == '/'){
			fichier.ignore(100,'/');
		}
		else if(type == 't'){
			
			float nbrCoord1;
			float nbrCoord2;
			fichier >> nbrCoord1;
			fichier >> nbrCoord2;
			
			if( nbrTexture < 30){
				(*texcoords)[nbrTexture].set(Vec2f::value_type(nbrCoord1),Vec2f::value_type(nbrCoord2));
				nbrTexture++;
			}
			else
				cout << "Fichier non supporte !" << endl;
		}
		else if(type == 'v'){
			for(int i = 0; i < 3;i++){
				fichier >> coord[i];
				
			}
			vertices->push_back(Vec3(coord[0],coord[1],coord[2]));
			
			formeBizarreVertices->setVertexArray(vertices);
		
		}
		else if(type == 'f' ){
			DrawElementsUInt* faceDessin =  new osg::DrawElementsUInt(osg::PrimitiveSet::POLYGON, 0);
			for(int i = 0; i < 4;i++){
				int face = 0;
				fichier >> face;
				
				faceDessin->push_back(face);
			}

			
			formeBizarreVertices->addPrimitiveSet(faceDessin);
			
		}

	}
	formeBizarreVertices->setTexCoordArray(0,texcoords);
	formeBizarreVertices->setStateSet(getTexture2D(texture));
	
	return formeBizarreVertices;
}

