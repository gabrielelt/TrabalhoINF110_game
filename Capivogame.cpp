#include <SFML/Graphics.hpp>
#include <iostream>
#include<cstring>

char mapa[17][23] = {    // Mapa do jogo
"1111111111111111111", 
"1000000000000000001",                               
"1010101011101011101",                    
"1010101010001011101",
"1010101010101011101", 
"1010101010001001001",
"1010001011101100001",
"1011111010001111101",
"1000000000000000001",
"1011111011111011101",   
"1010000010000010001",    
"1010111010111010101",   
"1010000010000010001",  
"1011111011111010111",  
"0000000000000000000", 
"1111111111111111111" 
};

int posxCarrapatoNatural = 9, posyCarrapatoNatural = 10;
int posxCarrapatoVermelho = 10, posyCarrapatoVermelho = 10;
int posxCarrapatoAzul = 9, posyCarrapatoAzul = 12;
int posxCarrapatoAmarelo = 10, posyCarrapatoAmarelo = 12; 

char gramas[17][23];
int cont;
double velocidade = 0.1;
int posVetorY = 9;
int posVetorX = 8;
double posx = 9.0;                                                                  // posicao da capivara
double posy = 8.0;                                                                           
bool right = false, left = false, down = false, up = false, iniciar = true;
bool capivaraSaltando = false, capivaraIntermediaria = false;                                     //posições de corrida da capivara

int main() {
   // cria a janela
   sf::RenderWindow window(sf::VideoMode(570, 480), "capirrapato");

   // shape da parede
   sf::RectangleShape quad(sf::Vector2f(30, 30));
   quad.setFillColor(sf::Color(190, 0, 255));
   
   //sprint das gramas   
   for (int i =0; i < 17; i++)
      for (int j = 0; j < 23; j ++){
         gramas[i][j] = mapa [i][j];
         if (gramas[i][j] == '0')
            cont++;
      }
   
   sf::Texture grama;                                      //capivara saltando (durante corrida)
   if (!grama.loadFromFile("grama.png")){
     std::cout << "Erro lendo imagem capivaraCorrendo.png\n";
     return 0;
   }
   sf::Sprite spriteGrama;
   spriteGrama.setTexture(grama);



   // sprites das capivaras
   sf::Texture texturaCapivaraSaltando;                                      //capivara saltando (durante corrida)
   if (!texturaCapivaraSaltando.loadFromFile("capivaraCorrendo.png")){
     std::cout << "Erro lendo imagem capivaraCorrendo.png\n";
     return 0;
   }
   sf::Sprite spriteCapivara;
   spriteCapivara.setTexture(texturaCapivaraSaltando);
   
    sf:: Texture texturaCapivaraInicial;                                      //capivara antes do primeiro movimento
   if (!texturaCapivaraInicial.loadFromFile("capivaraDeitada.png")){
   std::cout << "Erro lendo imagem capivaraDeitada.png\n";
   return 0;
   }
   sf::Sprite spriteCapivaraInicial;
   spriteCapivaraInicial.setTexture(texturaCapivaraInicial);
   
   
   sf:: Texture texturaCapivaraIntermediaria;                                    //capivara na fase intermediária da corrida
   if (!texturaCapivaraIntermediaria.loadFromFile("capivaraIntemediario.png")){
   std::cout << "Erro lendo imagem capivaraIntermediario.png\n";
   return 0;
   }
   sf::Sprite spriteCapivaraIntermediaria;
   spriteCapivaraIntermediaria.setTexture(texturaCapivaraIntermediaria);
   

    // sprites dos carrapatos
    
   sf::Texture texturaCarrapato;                                //natural
   if (!texturaCarrapato.loadFromFile("carrapato.png"))
	{
     std::cout << "Erro lendo imagem carrapato.png\n";
     return 0;
   }
   sf::Sprite spriteCarrapato;
   spriteCarrapato.setTexture(texturaCarrapato);
   
   sf::Texture texturaCarrapatoRed;                               //red
   if (!texturaCarrapatoRed.loadFromFile("carrapatoVermelho.png"))
	{
     std::cout << "Erro lendo imagem carrapato.png\n";
     return 0;
   }
   sf::Sprite spriteCarrapatoRed;            
   spriteCarrapatoRed.setTexture(texturaCarrapatoRed);
   
   sf::Texture texturaCarrapatoBlue;                              //blue
   if (!texturaCarrapatoBlue.loadFromFile("carrapatoAzul.png"))
	{
     std::cout << "Erro lendo imagem carrapato.png\n";
     return 0;
   }
   sf::Sprite spriteCarrapatoBlue;
   spriteCarrapatoBlue.setTexture(texturaCarrapatoBlue);
   
   sf::Texture texturaCarrapatoYellow;                            //yellow
   if (!texturaCarrapatoYellow.loadFromFile("carrapatoAmarelo.png"))
	{
     std::cout << "Erro lendo imagem carrapato.png\n";
     return 0;
   }
   sf::Sprite spriteCarrapatoYellow;
   spriteCarrapatoYellow.setTexture(texturaCarrapatoYellow);



  
   
	sf::Clock clock;

	// executa o programa enquanto a janela está aberta
   while (window.isOpen()) 
	{
      // verifica todos os eventos que foram acionados na janela desde a última iteração do loop
      sf::Event event;
      while (window.pollEvent(event))
		{
         // evento "fechar" acionado: fecha a janela
         if (event.type == sf::Event::Closed)
            window.close();

         // tecla pressionada
         if (event.type == sf::Event::KeyPressed) 
			{
            if (event.key.code == sf::Keyboard::Left)
				{
					left = true;
					right = up = down = false;
				}
            else if (event.key.code == sf::Keyboard::Right)
				{
					right = true;
					left = up = down = false;
				}
            else if (event.key.code == sf::Keyboard::Up)
				{
					up = true;
					right = left = down = false;
				}
            else if (event.key.code == sf::Keyboard::Down)
				{
					down = true;
					right = up = left = false;
				}
			}if ((left == 1 || right == 1 || up == 1 || down == 1) && capivaraSaltando == false){
			   capivaraSaltando == true;
            capivaraIntermediaria == false;
         }else if(capivaraSaltando == true){
         	capivaraSaltando == false;
            capivaraIntermediaria == true;
         }
		}
      if (clock.getElapsedTime() > sf::seconds(0.05)) // tempo desde último restart > 0.05s (velocidade inicial do jogo)
		{ 
         clock.restart();      // recomeça contagem do tempo
         bool cima= true, baixo = true, esquerda = true, direita = true;
         if (up && mapa[posVetorY-1][posVetorX] != '1' && cima){                                       //verifica se o pŕoximo passo será uma das paredes do mapa
            posy -= 0.25;
            if (posVetorY - posy > 0.99 && esquerda && direita) posVetorY --;
            if (posVetorY - posy > 0.5  && mapa[posVetorY-2][posVetorX] == '1') cima = false;
            if (gramas[posVetorY][posVetorX] == '0'){                                                 //verifica as gramas comidas e as retira do mapa
               gramas[posVetorY][posVetorX] = 1;
               cont--;
           }                                                                                 
         }if (down && mapa[posVetorY+1][posVetorX] != '1'){
				posy += 0.25;                 // muda a posição de acordo com booleano ativo
            if (posy - posVetorY > 0.99 && esquerda && direita)  posVetorY++;
            if (posy - posVetorY > 0.5 && mapa[posVetorY+2][posVetorX] == '1') baixo = false;
            if (gramas[posVetorY][posVetorX] == '0'){
               gramas[posVetorY][posVetorX] = 1;
               cont--;
           }                
         }if (left && mapa[posVetorY][posVetorX - 1] != '1'){ 
				posx -= 0.25;
				if (posVetorX - posx > 0.99 && cima && baixo) posVetorX--;
            if (posVetorX - posx > 0.5 && mapa[posVetorY][posVetorX - 1] == '1') esquerda == false;
			   if (gramas[posVetorY][posVetorX] == '0'){
               gramas[posVetorY][posVetorX] = 1;
               cont--;
               
           }                                                
			}if (right && mapa[posVetorY][posVetorX + 1] != '1'){ 
				posx += 0.25;
				if (posx - posVetorX > 0.99 && cima && baixo) posVetorX++;
				if (posx - posVetorX > 0.5 && mapa[posVetorY][posVetorX + 1] == '1') direita == false;
			   if (gramas[posVetorY][posVetorX] == '0'){
               gramas[posVetorY][posVetorX] = 1;
               cont--;
           }                
			}
      }
         std::cout << posx << " " << posVetorX << " " << posy << " " << posVetorY << std::endl;
         if (cont == 0) window.close();
         std::cout << cont << std:: endl;
    
         //velocidade -= 0.05; 
      // limpa a janela com a cor preta
      window.clear(sf::Color::Black);

      // desenhar tudo aqui...

      // desenha paredes
      for(int i=0;i<17;i++)
		{
      	for(int j=0;j<23;j++)
			{
            if (mapa[i][j]=='1')
				{
               quad.setPosition(j*30, i*30);
               window.draw(quad);
            }
			}
		}
		for (int i =0; i < 17; i++)
         for (int j = 0; j < 23; j ++)
            if (gramas[i][j] == '0'){
               spriteGrama.setPosition(j*30, i*30);
               window.draw(spriteGrama);
            }

      // desenha a capivara e o carrapato
      if(left== 0 && right == 0 && up==0 && down==0){
      spriteCapivaraInicial.setPosition(posx*30,posy*30);
      window.draw(spriteCapivaraInicial);
      }else{
      spriteCapivara.setPosition(posx*30,posy*30);
      window.draw(spriteCapivara);
	   //}else if (capivaraIntermediaria){
	   //spriteCapivaraIntermediaria.setPosition(posx*30,posy*30);
      //window.draw(spriteCapivaraIntermediaria);
	   }
	   spriteCarrapato.setPosition(posxCarrapatoNatural * 30,posyCarrapatoNatural*30);                           //posição carrapato natural
		window.draw(spriteCarrapato);                                     //imprimir carrapato nessa posição
		
		spriteCarrapatoRed.setPosition (posxCarrapatoVermelho*30,posyCarrapatoVermelho*30);                        //posição carrapato red
		window.draw(spriteCarrapatoRed);
		
		spriteCarrapatoBlue.setPosition  (posxCarrapatoAzul*30,posyCarrapatoAzul*30);                       //posição carrapato blue
		window.draw(spriteCarrapatoBlue);
		
		spriteCarrapatoYellow.setPosition   (posxCarrapatoAmarelo*30,posyCarrapatoAmarelo*30);                       //posição carrapato blue
		window.draw(spriteCarrapatoYellow);


      // termina e desenha o frame corrente
      window.display();
	}	
}
