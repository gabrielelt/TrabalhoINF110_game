#include <SFML/Graphics.hpp>
#include <iostream>

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

float posx = 9;                                                                  // posicao da capivara
float posy = 8;                                                                           
bool right = false, left = false, down = false, up = false, iniciar = true;
bool capivaraSaltando = false, capivaraIntermediaria = false;                                     //posições de corrida da capivara


int main() {
   // cria a janela
   sf::RenderWindow window(sf::VideoMode(570, 480), "capirrapato");

   // shape da parede
   sf::RectangleShape quad(sf::Vector2f(30, 30));
   quad.setFillColor(sf::Color(190, 0, 255));

   // sprites da capivara
   sf::Texture texturaCapivaraSaltando;
   if (!texturaCapivaraSaltando.loadFromFile("capivaraCorrendo.png")){
     std::cout << "Erro lendo imagem capivaraCorrendo.png\n";
     return 0;
   }
   sf::Sprite spriteCapivara;
   spriteCapivara.setTexture(texturaCapivaraSaltando);

	  // sprites do carrapato
   sf::Texture texturaCarrapato;
   if (!texturaCarrapato.loadFromFile("carrapato.png"))
	{
     std::cout << "Erro lendo imagem carrapato.png\n";
     return 0;
   }
   sf::Sprite spriteCarrapato;
   spriteCarrapato.setTexture(texturaCarrapato);

   sf:: Texture texturaCapivaraInicial;
   if (!texturaCapivaraInicial.loadFromFile("capivaraDeitada.png")){
   std::cout << "Erro lendo imagem capivaraDeitada.png\n";
   return 0;
   }
   //sprite capivara começo do jogo
   sf::Sprite spriteCapivaraInicial;
   spriteCapivaraInicial.setTexture(texturaCapivaraInicial);
   
   //capivara na fase intermediária da corrida
   sf:: Texture texturaCapivaraIntermediaria;
   if (!texturaCapivaraIntermediaria.loadFromFile("capivaraIntemediario.png")){
   std::cout << "Erro lendo imagem capivaraIntermediario.png\n";
   return 0;
   }
   //sprite capivara começo do jogo
   sf::Sprite spriteCapivaraIntermediaria;
   spriteCapivaraIntermediaria.setTexture(texturaCapivaraIntermediaria);
   
   
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
         if (up && mapa[(int)(posy-0.05)][(int)posx] != true)
				posy -= 0.05;     // muda a posição de acordo com booleano ativo
         if (down && mapa[(int)(posy+0.05)][(int)posx] != true)
				posy += 0.05;
         if (left && mapa[(int)posy][(int)(posx-0.05)] != true) 
				posx -= 0.05;
         if (right && mapa[(int)posy][(int)(posx+0.05)] != true) 
				posx += 0.05;
      }
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

      // desenha a capivara e o carrapato
      if(left== 0 && right== 0 && up==0 && down==0){
      spriteCapivaraInicial.setPosition(posx*30,posy*30);
      window.draw(spriteCapivaraInicial);
      }else{
      spriteCapivara.setPosition(posx*30,posy*30);
      window.draw(spriteCapivara);
	   //}else if (capivaraIntermediaria){
	   //spriteCapivaraIntermediaria.setPosition(posx*30,posy*30);
      //window.draw(spriteCapivaraIntermediaria);
	   }
	   spriteCarrapato.setPosition(8*30,8*30);
		window.draw(spriteCarrapato);

      // termina e desenha o frame corrente
      window.display();
	}	
}
