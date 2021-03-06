//
// Created by alex on 10/03/18.
//

#include "Partie.h"
#include "Persos/Pacman.h"
#include "Persos/Fantome.h"
#include "Persos/deplacement.h"
#include <SFML/Audio.hpp>

/*
Partie::pacman;
Partie::fantome1;
Partie::fantome2;
Partie::fantome3;
*/




Partie::Partie() : level(1)
        {
    Texture texturesPacman = Texture(), texturesFantome1 = Texture(), texturesFantome2 = Texture(), texturesFantome3 = Texture();
    if (!texturesPacman.loadFromFile("imgpacman/TexturesPacman.png"))
        throw ("Erreur lors du chargement des textures.");
    if (!texturesFantome1.loadFromFile("imgpacman/Ghost-B.png"))
        throw ("Erreur lors du chargement des textures.");
    if (!texturesFantome2.loadFromFile("imgpacman/Ghost-R.png"))
        throw ("Erreur lors du chargement des textures.");
    if (!texturesFantome3.loadFromFile("imgpacman/Ghost-Y.png"))
        throw ("Erreur lors du chargement des textures.");

}

Partie::~Partie() {

}

Partie &Partie::Instance() {
    static Partie p_instance = Partie();
    return p_instance;
}
void Partie::niveau3(Pacman &pacman,vector<Fantome*> fantomes, board &B, FenetreGrapheSFML &window) {

    cout << "Niveau 3 :" << endl;
    if(!B.aMangayTouteGommes())
    {
        deplacement::gestionPartie(pacman, fantomes, B, window.t, deplacement::gestionDeplacementFantomeLvl3);
    }
    else
    {
        cout << "Partie terminée ! " << endl;

    }

}

void Partie::niveau2(Pacman &pacman,vector<Fantome*> fantomes, board &B, FenetreGrapheSFML &window) {

    cout << "Niveau 2 :" << endl;
    if(!B.aMangayTouteGommes())
    {
        deplacement::gestionPartie(pacman, fantomes, B, window.t, deplacement::gestionDeplacementFantomeLvl2);
    }
    else
    {
        cout << "Niveau 2 terminé" <<endl;
        level++;
        B.reinitialiserGommes();
    }

}


void Partie::niveau1(Pacman &pacman,vector<Fantome*> fantomes, board &B, FenetreGrapheSFML &window) {

    cout << "Niveau 1 :" << endl;
    if(!B.aMangayTouteGommes())
    {
        deplacement::gestionPartie(pacman, fantomes, B, window.t, deplacement::gestionDeplacementFantomeLvl1);
    } else
    {
        cout << "Niveau 1 terminé" <<endl;
        level++;
        B.reinitialiserGommes();
    }

}

void Partie::gestionLevel(Pacman &pacman,vector<Fantome*> fantomes, board &B, FenetreGrapheSFML &window)
{
    switch(level)
    {
        case 1: niveau1(pacman,fantomes,B,window);
            break;
        case 2: niveau2(pacman,fantomes,B,window);
            break;
        case 3: niveau3(pacman,fantomes,B,window);
            break;
    }
}


void Partie::lancerPartie(FenetreGrapheSFML &window, Pacman &pacman, vector<Fantome*> fantomes,
                     board &B) {

    Font font;

    Text scoreAffiche, gameOver;

    if (!font.loadFromFile("KINKEE.TTF"))
    {
        throw ("Erreur lors du chargement de la police du score");
    }
    scoreAffiche.setFont(font);
    gameOver.setString("Game Over");
    gameOver.setCharacterSize(72);
    gameOver.setFont(font);
    gameOver.setColor(Color::White);
    gameOver.setPosition(vecteur2DToVector2f(window.t.applique(Vecteur2D(0.5, 1.5))));
    srand(static_cast<unsigned int>(time(NULL)));
    float deltatime;
    Clock clock;
    while (window.fenetre.isOpen())
    {


        sf::Event event{};
        deltatime = clock.restart().asSeconds();
        while (window.fenetre.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                {
                    window.fenetre.close();
                    break;
                }
                default:
                    break;
            }
            gestionLevel(pacman,fantomes,B,window);
            if(!pacman.getEtat())
            {
                //window.fenetre.clear();
                sf::Music fin;
                if (!fin.openFromFile("pac-man-end-game.wav"))
                    throw ("Erreur lors du chargement de la musique de fin.");
                fin.play();
                window.fenetre.draw(gameOver);
                window.fenetre.display();
                sleep(seconds(2.0f));
                window.fenetre.close();
            }
        }



        String s = "Score : " + to_string(B.score);
        scoreAffiche.setString(s);
        scoreAffiche.setCharacterSize(26);
        scoreAffiche.setColor(Color::White);
        scoreAffiche.setPosition(vecteur2DToVector2f(window.t.applique(Vecteur2D(1.5, -0.75))));
        window.fenetre.clear();
        window.fenetre.draw(scoreAffiche);
        B.graphe.dessine(window);
        fantomes[0]->Update(deltatime);
        fantomes[0]->dessine(window);
        fantomes[1]->Update(deltatime);
        fantomes[1]->dessine(window);
        fantomes[2]->Update(deltatime);
        fantomes[2]->dessine(window);
        pacman.Update(deltatime);
        pacman.dessine(window);
        //window.fenetre.draw(gameOver);
        window.fenetre.display();
    }
}


