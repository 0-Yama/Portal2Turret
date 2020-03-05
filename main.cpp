
/*********************************************************/
/*        TP1: primitives 2D et transformations          */
/*********************************************************/
/*													     */
/*       ESGI: Algorithmiques pour l'infographies		 */
/*													     */
/*********************************************************/
/*													     */
/*  Objectif: afficher des formes 2D et les transformer  */
/*													     */
/*********************************************************/



#include<windows.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
//#include <GL/glut.h>
#endif
#include<math.h>
#include<glut.h>
#include<stdlib.h>
#include<stdio.h>




float alpha    = 0.0;
float phi      = 0.0;
float rayon    = 5.0;
float pasAngle = 0.1;
float pasRayon = 0.1;
/* prototypes de fonctions */
void initRendering();                           // Initialisation du rendu
void display();                             // mod�lisation
void reshape(int w,int h);                      // visualisation
void update(int value);                         // mise � jour: appelle Timer pour l'animation de la sc�ne
void keyboard(unsigned char key, int x, int y); // fonction clavier




float F1x(float x){
    return x*x-0.25*x;
}
float F2x(float x){
    return x*x*0.25;
}


/* Programme principal */
int main(int argc,       // argc: nombre d'arguments, argc vaut au moins 1
		  char **argv){  // argv: tableau de chaines de caract�res, argv[0] contient le nom du programme lanc� (plus un �ventuel chemin)


	/* Initialisation de glut et creation de la fenetre */
    glutInit(&argc, argv);                       // Initialisation
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); // mode d'affichage RGB, et test prafondeur
    glutInitWindowSize(500, 500);                // dimension fen�tre
	glutInitWindowPosition (100, 100);           // position coin haut gauche
	glutCreateWindow("TP1: formes 2D et transformation");  // nom

	/* Initialisation d'OpenGL */
	initRendering();

	/* Enregistrement des fonctions de rappel
     => initialisation des fonctions callback appel�es par glut */
    glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	/* rq: le callback de fonction (fonction de rappel) est une fonction qui est pass�e en argument � une
	autre fonction. Ici, le main fait usage des deux fonctions de rappel (qui fonctionnent en m�me temps)
	alors qu'il ne les conna�t pas par avance.*/


	/* Entr�e dans la boucle principale de glut, traitement des �v�nements */
    glutMainLoop();         // lancement de la boucle de r�ception des �v�nements
    return 0;               // pour finir
}


/* Initialisation d'OpenGL pour le rendu de la sc�ne */
void initRendering() {

    /* Active le z-buffer */
    glEnable(GL_DEPTH_TEST);

	/* Activation des couleurs */
	glEnable(GL_COLOR_MATERIAL);

	/* d�finit la couleur d'effacement et la couleur de fond */
	glClearColor(0.0, 0.0, 0.0, 0.0);

	/*  d�finit la taille d'un pixel*/
	glPointSize(2.0);

}

/* Cr�ation de la sc�ne */
void display(){

	/* Efface les tampons de couleur et de profondeur de l'image avec la couleur de fond.
	rq: buffer: m�moire tampon, c'est donc une surface en memoire utilis�e pour stocker une image*/
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	/* la mat de visualisation-mod�lisation est modifiable par d�faut */
	glMatrixMode(GL_MODELVIEW);

	/* on charge l'identit� dans la matrice de mod�lisation-visualisation*/
	glLoadIdentity();


	/* Permet de cr�er un point de vue. D�finit une matrice de mod�lisation-visualisation et la multiplie
	� droite de lma matrice active, ici l'identit�*/

	gluLookAt((rayon*cos(phi)*sin(alpha)), (rayon*sin(phi)), (rayon*cos(phi)*cos(alpha)),      // position cam�ra
		      0.0, 0.0, 0.0,      // point de mire
			  0.0, 1.0, 0.0);     // vecteur d'orientation cam�ra






	/* A vous de jouer */

    glPushMatrix();
        float scale = 0.125;
        glScalef(scale,scale,scale);
        for(float x = 0;x<=3;x+=0.00001){
            glBegin(GL_TRIANGLES);

                glVertex3f(0,0,0);   glVertex3f(0,F1x(x),0);   glVertex3f(x,F1x(x),F2x(x));
                glVertex3f(0,0,0);   glVertex3f(0,F1x(x),0);   glVertex3f(-x,F1x(x),F2x(x));

                if(x<=2){
                    if(x<1.5){
                        glVertex3f(0,F1x(3),0);   glVertex3f(0,F1x(3)+F1x(x),0);   glVertex3f(x/3+3,F1x(3)+F1x(x),F2x(x/3+3));
                        glVertex3f(0,F1x(3),0);   glVertex3f(0,F1x(3)+F1x(x),0);   glVertex3f(-(x/3+3),F1x(3)+F1x(x),F2x(x/3+3));
                    }else{
                        glVertex3f(0,F1x(3),0);   glVertex3f(0,F1x(3)+F1x(x),0);   glVertex3f(((3-x)/3)+3,F1x(3)+F1x(x),F2x(x/3+3));
                        glVertex3f(0,F1x(3),0);   glVertex3f(0,F1x(3)+F1x(x),0);   glVertex3f(-(((3-x)/3)+3),F1x(3)+F1x(x),F2x(x/3+3));
                    }

                }


            glEnd();
        }

    glPopMatrix();


	/* On swap (�change) les buffers, c�d, on fait passer l'image calcul�e et dessin�e
	dans le back buffer au buffer qui va l'afficher: le front buffer (en g�n�ral), c'est le bouble buffering
	Cela �vite une image anim�e sacad�e, si elle �tait directement trac�e dans le front buffer*/
	glutSwapBuffers();

	/* On force l'affichage */
	glFlush(); // nettoie les fen�tres pr�c�dentes
}



/*  Mise en forme de la sc�ne pour l'affichage */
void reshape(int w,  // w: largeur fen�tre
			 int h)  // h: hauteur fen�tre
{
	/* Viewport: cadrage. Sp�cifie la r�gion (position et taille en px) que l'image observ�e de la sc�ne occupe
	� l'�cran => r�duction et agrandissement de l'image possible*/
	glViewport(0, 0,(GLsizei) w, (GLsizei) h);

	/* Sp�cifie que la matrice de projection va �tre modifi�e  */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();             // matrice courante: l'identit�
	//glOrtho(-2.0, 2.0, -2.0, 2.0, 1.5, 20.0);
	//glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);

	/* Perspective avec point de fuite */
	gluPerspective(60.0,                       // angle d'ouverture vertical cam�ra
				   (GLfloat) w / (GLfloat) h,  // ratio largeur-hauteur
				   1.0,						   // plan proche z=1
				   200.0);                     // plan �loign� z=200


}

/* Fonction de gestion du clavier */
void keyboard(unsigned char key,       // Touche qui a �t� press�e
                    int x, int y) {    // Coordonn�es courante de la souris

		switch (key){
            case 's':
                phi+=phi<3.14/2-pasAngle?pasAngle:0;
                glutPostRedisplay();
                break;
             case 'z':
                phi-=phi>-3.14/2+pasAngle?pasAngle:0;
                glutPostRedisplay();
                break;
            case 'd':
                alpha-=alpha==0?6.28:pasAngle;
                glutPostRedisplay();
                break;
             case 'q':
                alpha+=alpha==6.28?-6.28:pasAngle;
                glutPostRedisplay();
                break;
            case 'a':
                rayon+=pasRayon;
                glutPostRedisplay();
                break;
             case 'e':
                rayon-=rayon==3?0:pasRayon;
                glutPostRedisplay();
                break;
			case 'w':   /* Quitter le programme */
				exit(0);
		}
}
