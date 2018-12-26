#include "Interface.h"

using namespace std;

int Navios::IncNavio = 1;

void Interface::start() {

	Prompt();

}

void Interface::acrescentaMoedas(int moedas) {

	jogador.setMoedas(jogador.getMoedas() + moedas);
}
void Interface::gotoComando() {
	Consola::gotoxy(0, 23);
}
void Interface::gotoErro() {
	//Consola::gotoxy(60,23);
	Consola::gotoxy(0,26);
}
void Interface::gotoPrint() {
	Consola::gotoxy(45, 27);
}
string Interface::GeradorEvento()
{
	ostringstream os;

	int op;
	
	while (mundo.getExistenciaEvento() != EVENTO_ON) {
			
			op = rand() % 4 + 1;
	
			switch (op)
			{
				case EVENTO_TEMPESTADE:
					os << "Vai ser Gerada uma Tempestade " << endl;
					if ((rand() % 100 + 1) <= this->probTempestade) {

						gotoErro();
						
						os << mundo.trataEventos(EVENTO_TEMPESTADE) << endl;
						}
						return os.str();
					
				break;
				case EVENTO_SEREIAS:
					os << "Vai ser Gerado um Ataque de Sereias " << endl;
					if ((rand() % 100 + 1) <= this->probSereias) {

						gotoErro();
						
						cout << mundo.trataEventos(EVENTO_SEREIAS) << endl;
						}
						return os.str();
					
					
					break;
				case EVENTO_CALMARIA:

					os << "Vai ser Gerado um Evento Calmaria " << endl;
					
					if ((rand() % 100 + 1) <= this->probCalmaria) {
					
						os << mundo.criaEvento(&mundo, EVENTO_CALMARIA) << endl;
						
					}
					return os.str();
					break;
				case EVENTO_MOTIM:
	
					if ((rand() % 100 + 1) <= this->probMotin) {

						if (mundo.VerificaExistenciaNavios() == true ) {

							os << "Vai ser Gerado um Evento Motim " << endl;

							os << mundo.criaEvento(&mundo, EVENTO_MOTIM) << endl;
						}
						else
							os << "Nao existem navios no Mundo para efetuar o Evento Motim" << endl;
					}
					return os.str();
					break;
			}
		}
	return os.str();
}
int Interface::verificaFimdoJogo() {

	int navJogador = 0, navPirata = 0, nPortosAmigos = 0, nPortosInimigos=0;

	const vector <const Navios *>  auxNavio = mundo.getVetorNavios();
	const vector <const Navios *>  auxNavioJogador = jogador.getVetorNaviosJogador();
	const vector <const Porto *>  auxPorto = mundo.getVetorPorto();

	for (unsigned int i = 0; i < auxNavio.size(); i++) {
		if (auxNavio[i]->getEstado() == normal || auxNavio[i]->getEstado() == aDeriva) 
			navJogador++;
		if (auxNavio[i]->getEstado() == pirata)
			navPirata++;
	}

	
	for (unsigned int i = 0; i < auxPorto.size(); i++) {
		if (auxPorto[i]->getChar() >= 'A' && auxPorto[i]->getChar() <= 'Z') {
			nPortosAmigos++;
		}
		if (auxPorto[i]->getChar() >= 'a' && auxPorto[i]->getChar() <= 'z') {
			nPortosInimigos++;
		}	
	}

	if (navJogador > 0 && nPortosInimigos == 0 && navPirata==0) {
		Consola::clrscr();
		Consola::gotoxy(20, 7);
		Consola::setTextSize(60,60);
		cout << "Parabens!!! Ganhou o Jogo!!!" << endl;
		cin.get();
		return 1;
	}
	if (navJogador == 0 && nPortosAmigos == 0 && nPortosInimigos > 0 && navPirata > 0) {
		Consola::clrscr();
		Consola::gotoxy(20, 7);
		Consola::setTextSize(60, 60);
		cout << "Parabens!!! Perdeu o Jogo!!!" << endl;
		cin.get();
		return 1;
	}

	return 0;

}
// Metodo Prompt tem como objetivo tratar os comandos introduzidos pelo Jogador	
void Interface::Prompt() {

	string linha, acao, configFile;

	Consola::VERDE;

	gotoComando();
	cout << "Comando: config ";

	getline(cin, linha);

	/*
	______________________________________________________________________________________

					iniciar a fase 1: trata comando config
	______________________________________________________________________________________
	*/
	PromptFase1(linha);
	//inicializa��o do jogador
	jogador.setMundo(&mundo);
	//moedas
	jogador.setMoedas(moedas);
		//atribui��o do porto principal
	jogador.setPortoPrincipal( mundo.getPortoPrincipal() );
	//chamar aqui o verificar porto bem

	//
	/*
	______________________________________________________________________________________

					iniciar a fase 2: Trata comandos do jogador
	______________________________________________________________________________________
	*/
	do {

		Consola::VERDE;

		gotoComando();
		cout << "Comando: ";

		getline(cin, linha);

		PromptFase2(linha);
		//if (verificaFimdoJogo()==1)return;
		
		jogador.setPortoPrincipal(mundo.getPortoPrincipal());
		mundo.retiraNavAfundados(); //mudar para dentro quando for implemento do ciclo do navios
		mundo.abasteceNaviosNosPortos();
		cout << jogador.moveNavioAuto();
		cout << mundo.moveNavioPirataAuto();
		mundo.verificaaDeriva();
		mundo.retiraNavAfundados();

		if (mundo.getExistenciaEvento() == EVENTO_OFF) {
			gotoErro();
			cout << GeradorEvento();
		}
		else {
			gotoErro();
			cout << mundo.trataEventos();
			if (mundo.VerificaTipoEventoEmExecucao() == true) {
				gotoErro();
				cout << "Existe um evento Calmaria a decorrer..!" << endl;
			}
			else {
				gotoErro();
				cout << "Existe um evento Motim a decorrer..!" << endl;
			}
		}
		//execu��o de comando pendentes | comportamentos automaticos
		//combates
		//eventos
		//piratas

		mostraMapa();
	
		Consola::getch();

		Consola::clrscr();

		mostraMapa();

		this->Turno = this->incTurno++;

	} while (linha != "sair");


}
int Interface::FiltaComandos(string acao) {

	vector< string > comandos = {"exec", "prox", "compranav", "vendenav", "lista", "compra", "vende", "move", "auto", "stop", "pirata","evpos","evnav",
								  "moedas", "evpos", "evnav","pirata","vaipara", "comprasold", "saveg", "loadg", "delg"};

	for (unsigned int i = 0; i < comandos.size(); i++) {
		if (comandos[i].compare(acao) == 0)
			return i + 1;
	}
	return 0;
}
void Interface::PromptFase1(string linha) {

	if (count(linha.begin(), linha.end(), ' ') == 0) {

		if (carregaFich(linha)) {
			gotoErro();
			if (!mundo.portosBemColocado()) {
				mundo.limpaVetores();

				carregaFich(configInit);
			}
			cout << "Ficheiro introduzido carregado com sucesso .. !" << endl;
		}
		else {
			gotoErro();
			carregaFich(configInit);
			cout << " [ Erro ao carregar ficheiro ] Ficheiro por default carregado com Sucesso.. !" << endl;

		}
	}
	else {
		carregaFich(configInit);
		gotoErro();
		cout << " [ Erro ao carregar ficheiro ] Ficheiro por default carregado com Sucesso.. !" << endl;
	}
}
int Interface::verificaDadosFicheiro(string linha) {

	vector < string > dadosEntrada = { "linhas", "colunas" , "moedas" , "probpirata", "preconavio", "precosoldado", "precovendpeixe",  "precocompmercad" ,
										"precovendmercad", "soldadosporto", "probevento" , "probtempestade" , "probsereias" , "probcalmaria", "probmotin" };

	for (unsigned int i = 0; i < dadosEntrada.size(); i++) 
		if (linha.compare(dadosEntrada[i]) == 0)
			return i + 1;
	

	return 0;
}
bool Interface::carregaFich(string configFile) {

	fstream fp;

	int inteiro, contaColunas = 0, flag = 0;
	string linha;

	
	if (!fp.is_open()) {
		fp.open(configFile);
		if (!fp.is_open())
			return false;
	}
	while (getline(fp, linha)) {

		istringstream buffer(linha);

		if (buffer >> linha && buffer >> inteiro) {

			switch (verificaDadosFicheiro(linha)) {

				case nlinhas:
					mundo.setDimY(inteiro);
					break;
				case ncolunas:
					mundo.setDimX(inteiro);
					
					break;
				case nmoedas:
					this->moedas = inteiro;
					break;
				case probpirata:
					this->probPirata = inteiro;
					break;
				case preconavio:
					this->precoNavio = inteiro;
					break;
				case precosoldado:
					this->precoSoldado = inteiro;
					break;
				case precovendpeixe:
					this->precoVendePeixe = inteiro;
					break;
				case precocompmercad:
					this->precoCompraMercadoria = inteiro;
					break;
				case precovendmercad:
					this->precoVendaMercadoria = inteiro;
					break;
				case soldadosporto:
					this->soldadosPorto = inteiro;
					break;
				case probevento:
					this->probVento = inteiro;
					break;
				case probtempestade:
					this->probTempestade = inteiro;
					break;
				case probsereias:
					this->probSereias = inteiro;
					break;
				case probcalmaria:
					this->probCalmaria = inteiro;
					break;
				case probmotin:
					this->probMotin = inteiro;
					break;
			}
		}
		else {
			buffer >> linha;
			for (int i = 0; i < mundo.getDimX(); i++) {
				if (linha[i] == '.') {

					this->mundo.criaSuperficie(i, contaColunas, linha[i]);
				}
				if (linha[i] == '+') {

					this->mundo.criaSuperficie(i, contaColunas, linha[i]);
				}
				if (linha[i] >= 'A' && linha[i] <= 'Z' || linha[i] >= 'a' && linha[i] <= 'z') {

					this->mundo.criaCelulaPorto(i, contaColunas,linha[i] );

				}
			}
			contaColunas++;
		}
	}
	fp.close();
	return true;
}
int Interface::ValidaCompraJogador(char tipoNavio) {
	switch (tipoNavio) {
	case 'V':
		if (jogador.validaCompra(PRECO_VELEIRO)) {
			jogador.setMoedas((jogador.getMoedas() - PRECO_VELEIRO));
			return 0;
		}
		else
			return -1;
		break;
	case 'G':
		if (jogador.validaCompra(PRECO_GALEAO)) {
			jogador.setMoedas((jogador.getMoedas() - PRECO_GALEAO));
			return 0;
		}
		else
			return -1;
		break;
	case 'E':
		if (jogador.validaCompra(PRECO_ESCUNA)) {
			jogador.setMoedas((jogador.getMoedas() - PRECO_ESCUNA));
			return 0;
		}
		else
			return -1;
		break;
	case 'F':
		if (jogador.validaCompra(PRECO_FRAGATA)) {
			jogador.setMoedas((jogador.getMoedas() - PRECO_FRAGATA));
			return 0;
		}
		else
			return -1;
		break;
	case 'S':
		if (jogador.validaCompra(PRECO_SUBMARINO)) {
			jogador.setMoedas((jogador.getMoedas() - PRECO_SUBMARINO));
			return 0;
		}
		else
			return -1;
		break;
	}
	return -2;
}
int Interface::compraNavio(char tipo) {

	int validacaoCompra = 0;

	if (jogador.getPortoPrincipal() >= 'A' && jogador.getPortoPrincipal() <= 'Z') {

		validacaoCompra = ValidaCompraJogador(tipo);

		if (validacaoCompra == COMPRA_COM_SUCESSO) {
			jogador.addNavioJogador(&mundo.criaNavio(&mundo,jogador.getPortoPrincipal(), tipo));
		}
	}
	return validacaoCompra;
}
int Interface::ValidaDirecoes(string direcao) {

	vector <string> direcoes = { "C", "B", "E", "D", "CE", "CD", "BE", "BD" };

	for (unsigned int i = 0; i < direcoes.size(); i++) {
		if (direcoes[i].compare(direcao) == 0)

			return (i + 1);

		}
	return naoMove;
}
void Interface::PromptFase2(string linha) {

	char tipo;
	string acao, direcao;
	int idNavio,x,y;
	istringstream buffer(linha);
	
	
	if (buffer >> acao) {
		switch (FiltaComandos(acao)) {
		case com_exec:
			gotoErro();
			cout << "[ COMANDO : " << acao << " ainda nao Implementado ] " << endl;
			break;
		case com_prox:
			gotoErro();
			cout << "[ COMANDO : " << acao << " ainda nao Implementado ] " << endl;
			break;
		case com_compranav:
			buffer >> tipo;
			if (tipo == 'V' || tipo == 'G' || tipo == 'E' || tipo == 'F' || tipo == 'S' && count(linha.begin(), linha.end(), ' ') == 1) {

				if (compraNavio(tipo) == COMPRA_COM_SUCESSO) {
					gotoPrint();
					cout << "Compra efetuada com sucesso!" << endl;
				}
				else if (compraNavio(tipo) == COMPRA_SEM_MOEDAS) {
					gotoErro();
					cout << "Compra n�o efetuada <-> Jogador Sem Moedas" << endl;
				}
				else if ((compraNavio(tipo) == TIPO_NAVIO_INVALIDO)) {
					gotoErro();
					cout << "Compra nao efetuada <-> N�o existe porto principal" << endl;
				}
			}
			else {
				gotoErro();
				cout << " [ Sintaxe " << acao << " Invalida..! Sintaxe :" << acao << " <N> ]" << endl;
				gotoPrint();
				cout << "Saldo atual do Jogador: " << jogador.getMoedas() << endl;
			}
			gotoPrint();
			cout << "Saldo atual do Jogador: " << jogador.getMoedas() << endl;
			//mostraNaviosJogador();
			break;
		case com_vendenav:
			gotoErro();
			if (buffer >> tipo) {
				acrescentaMoedas(jogador.vendeNavio(tipo, precoSoldado));
			}
			break;
		case com_lista:
			gotoErro();
			cout << "[ COMANDO : " << acao << " ainda nao Implementado ] " << endl;
			break;
		case com_compra:
			gotoErro();
			cout << "[ COMANDO : " << acao << " ainda nao Implementado ] " << endl;
			break;
		case com_vende:
			gotoErro();
			cout << "[ COMANDO : " << acao << " ainda nao Implementado ] " << endl;
			break;
		case com_move:
			if (buffer >> idNavio && buffer >> direcao && count(linha.begin(), linha.end(), ' ') == 2) {
				Navios *auxNavio=nullptr;
				if (ValidaDirecoes(direcao))
					if (jogador.validaIdNavio(idNavio) == true)
						if (!jogador.verificaModoAutomaticoNavio(idNavio)) {
							jogador.moveNavioJogador(idNavio, ValidaDirecoes(direcao));//com sucesso
								auxNavio = mundo.getNavio(idNavio);
								Consola::setTextColor(Consola::BRANCO);
								Consola::gotoxy(0, 26);
								cout << auxNavio->combate(CELULA_NAVIO_PIRATA);
						}
						else
							cout << "[ Erro..! AutoMove do Navio : " << idNavio << " esta ativo ..! ]" << endl;
					else
						cout << "[ Erro..! Id : " << idNavio << " de Navio Invalido ..! ]" << endl;
				else 
					cout << "[ Erro..! Direcao : " << direcao << " de Navio Invalido ..! ]" << endl;
			}
			else {
				gotoErro();
				cout << " [ Sintaxe " << acao << "Invalida..! Use" << acao << "<N> <X> || nota: X = C,B,D,E,CE,CD,BE,BD ]" << endl;
			}
			break;
		case com_auto:
			if (buffer >> idNavio && count(linha.begin(), linha.end(), ' ') == 1) {
				if (jogador.validaIdNavio(idNavio)) 
					jogador.AlteraAutoMoveNavio(idNavio, autoMove);
				else {
					gotoErro();
					cout << "[ Id introduzido: " << idNavio << " invalido  ]" << endl;
				}
			}
			else {
				gotoErro();
				cout << "[ COMANDO : " << acao << " ainda nao Implementado ] " << endl;
			}
			break;
		case com_stop:
			if (buffer >> idNavio && count(linha.begin(), linha.end(), ' ') == 1) {
				if (jogador.validaIdNavio(idNavio) == true)
					jogador.AlteraAutoMoveNavio(idNavio, normal);
			}
			else {
				gotoErro();
				cout << " [ Erro..! o comando introduzido est� incorrecto... Sitaxe: stop <ID_N>  ]" << endl;
			}
		
	break;
	case com_pirata:
		if (buffer >> tipo && buffer >> x && buffer >> y && count(linha.begin(), linha.end(), ' ') == 3) {

			if (tipo == 'V' || tipo == 'F') {
				if (x >= 0 && x < mundo.getDimX() && y >= 0 && y < mundo.getDimY()) {
					if (mundo.verificaCelulaMar(x, y) == CELULA_MAR && mundo.verificaCelulaNavio(x,y)!= CELULA_NAVIO) {
						mundo.criaNavPirata(&mundo, tipo, x, y);
					}
					}
			}
		}
		
		break;
	case com_evpos:
		gotoErro();
		cout << "[ COMANDO : " << acao << " ainda nao Implementado ] " << endl;
		break;
	case com_evnav:
		gotoErro();
		cout << "[ COMANDO : " << acao << " ainda nao Implementado ] " << endl;
		break;
	case com_moedas:
		
		if (buffer >> idNavio) {
			acrescentaMoedas(idNavio);// neste caso idNavio � o nr de moedas que o jogador introduziu
		}
		break;
	case com_vaipara:
		//este comando tem overload devido aos parametros vaipara <N> <x> <y> e vai para <N> <P>
		if (buffer >> idNavio && buffer >> x && buffer >> y) {
			mundo.vaiPara(idNavio, x, y);
		}
		break;
	case com_comprasold:
		gotoErro();
		cout << "[ COMANDO : " << acao << " ainda nao Implementado ] " << endl;
		break;
	case com_saveg:
		gotoErro();
		cout << "[ COMANDO : " << acao << " ainda nao Implementado ] " << endl;
		break;
	case com_loadg:
		gotoErro();
		cout << "[ COMANDO : " << acao << " ainda nao Implementado ] " << endl;
		break;
	case com_delg:
		gotoErro();
		cout << "[ COMANDO : " << acao << " ainda nao Implementado ] " << endl;
		break;
	default:
		if (acao != "sair") {
			gotoErro();
			cout << " [ ERRO..! Comando Incorreto..!  ]" << endl;
		}
	}
}
}
void Interface::mostraLegAndConfig() {

	Consola::setTextColor(Consola::BRANCO);

	Consola::gotoxy(44, 0);
	cout << "Legenda do Mapa";

	Consola::gotoxy(45, 2);
	cout << "\tMar -> azul";

	Consola::gotoxy(45, 3);
	cout << "\tTerra -> amarelo";

	Consola::gotoxy(45, 4);
	cout << "\tPortos -> A-Z Amigos";

	Consola::gotoxy(45, 5);
	cout << "\tPortos -> a-z Inimigos";

	Consola::gotoxy(84, 0);
	cout << "Configuracoes Iniciais: ";
	Consola::gotoxy(87, 2);
	cout << "Moedas: " << this->moedas<<endl;
	Consola::gotoxy(87, 3);
	cout << "Moedas Atuais: " <<  jogador.getMoedas();
	Consola::gotoxy(87, 4);
	cout << "Probalidade Pirata " << this->probPirata;
	Consola::gotoxy(87, 5);
	cout << "Preco Navio " << this->precoNavio;
	Consola::gotoxy(87, 6);
	cout << "Preco Soldado " << this->precoSoldado;
	Consola::gotoxy(87, 7);
	cout << "Preco Vende Peixe " << this->precoVendePeixe;
	Consola::gotoxy(87, 8);
	cout << "Preco Compra Mercadoria " << this->precoCompraMercadoria;
	Consola::gotoxy(87, 9);
	cout << "Preco Vende Mercadoria " << this->precoVendaMercadoria;
	Consola::gotoxy(87, 10);
	cout << "Soldados Porto " << this->soldadosPorto;
	Consola::gotoxy(87, 11);
	cout << "Probabilidade Vento " << this->probVento;
	Consola::gotoxy(87, 12);
	cout << "Probabilidade Tempestade " << this->probTempestade;
	Consola::gotoxy(87, 13);
	cout << "Probabilidade Sereias " << this->probSereias;
	Consola::gotoxy(87, 14);
	cout << "Probabilidade Calmaria " << this->probCalmaria;
	Consola::gotoxy(87, 15);
	cout << "Probabilidade Motin " << this->probMotin;

}
void Interface::mostraSuperficie() {

	const vector <const Superficie *>  auxSuperficie = mundo.getVetorSuperficie();

	for (unsigned int i = 0; i < auxSuperficie.size(); i++) {
		
		unsigned int x = auxSuperficie[i]->getX();
		unsigned int y = auxSuperficie[i]->getY();
		x *= 2;
		y *= 2;
		
		if (auxSuperficie[i]->VerificaCelulaMar() ) {
			
			if (i % 2 == 0) {
				Consola::gotoxy(x, y);
				Consola::setTextColor(Consola::AZUL);
				cout << char(254);

				Consola::gotoxy(x + 1, y);
				Consola::setTextColor(Consola::AZUL);
				cout << char(254);

				Consola::gotoxy(x, y + 1);
				Consola::setTextColor(Consola::AZUL);
				cout << char(254);

				Consola::gotoxy(x + 1, y + 1);
				Consola::setTextColor(Consola::AZUL);
				cout << char(254);
			}
			if (i % 2 != 0) {
				Consola::gotoxy(x, y);
				Consola::setTextColor(Consola::AZUL_CLARO);
				cout << char(254);

				Consola::gotoxy(x + 1, y);
				Consola::setTextColor(Consola::AZUL_CLARO);
				cout << char(254);

				Consola::gotoxy(x, y + 1);
				Consola::setTextColor(Consola::AZUL_CLARO);
				cout << char(254);

				Consola::gotoxy(x + 1, y + 1);
				Consola::setTextColor(Consola::AZUL_CLARO);
				cout << char(254);
			}

		}
		if (!auxSuperficie[i]->VerificaCelulaMar()) {
			if (i % 2 == 0) {
				Consola::gotoxy(x, y);
				Consola::setTextColor(Consola::AMARELO);
				cout << char(254);

				Consola::gotoxy(x + 1, y);
				Consola::setTextColor(Consola::AMARELO);
				cout << char(254);

				Consola::gotoxy(x, y + 1);
				Consola::setTextColor(Consola::AMARELO);
				cout << char(254);

				Consola::gotoxy(x + 1, y + 1);
				Consola::setTextColor(Consola::AMARELO);
				cout << char(254);
			}
			if (i % 2 != 0) {
				Consola::gotoxy(x, y);
				Consola::setTextColor(Consola::AMARELO_CLARO);
				cout << char(254);

				Consola::gotoxy(x + 1, y);
				Consola::setTextColor(Consola::AMARELO_CLARO);
				cout << char(254);

				Consola::gotoxy(x, y + 1);
				Consola::setTextColor(Consola::AMARELO_CLARO);
				cout << char(254);

				Consola::gotoxy(x + 1, y + 1);
				Consola::setTextColor(Consola::AMARELO_CLARO);
				cout << char(254);
			}
		}
	}

}
void Interface::mostraPortos() {

	const vector <const Porto *>  auxPorto = mundo.getVetorPorto();

	for (unsigned int i = 0; i < auxPorto.size(); i++) {
		unsigned int x = auxPorto[i]->getX();
		unsigned int y = auxPorto[i]->getY();

		x *= 2;
		y *= 2;

		if (auxPorto[i]->getChar() >= 'A' && auxPorto[i]->getChar() <= 'Z') {

			if (i % 2 == 0) {
				Consola::gotoxy(x, y);
				Consola::setTextColor(Consola::VERDE);
				cout << auxPorto[i]->getChar();

				Consola::gotoxy(x + 1, y);
				Consola::setTextColor(Consola::VERDE);
				cout << auxPorto[i]->getChar();

				Consola::gotoxy(x, y + 1);
				Consola::setTextColor(Consola::VERDE);
				cout << auxPorto[i]->getChar();

				Consola::gotoxy(x + 1, y + 1);
				Consola::setTextColor(Consola::VERDE);
				cout << auxPorto[i]->getChar();
			}
			if (i % 2 != 0) {
				Consola::gotoxy(x, y);
				Consola::setTextColor(Consola::VERDE_CLARO);
				cout << auxPorto[i]->getChar();

				Consola::gotoxy(x + 1, y);
				Consola::setTextColor(Consola::VERDE_CLARO);
				cout << auxPorto[i]->getChar();

				Consola::gotoxy(x, y + 1);
				Consola::setTextColor(Consola::VERDE_CLARO);
				cout << auxPorto[i]->getChar();

				Consola::gotoxy(x + 1, y + 1);
				Consola::setTextColor(Consola::VERDE_CLARO);
				cout << auxPorto[i]->getChar();
			}
		}

		if (auxPorto[i]->getChar() >= 'a' && auxPorto[i]->getChar() <= 'z') {
			if (i % 2 == 0) {
				Consola::gotoxy(x, y);
				Consola::setTextColor(Consola::VERMELHO);
				cout << auxPorto[i]->getChar();

				Consola::gotoxy(x + 1, y);
				Consola::setTextColor(Consola::VERMELHO);
				cout << auxPorto[i]->getChar();

				Consola::gotoxy(x, y + 1);
				Consola::setTextColor(Consola::VERMELHO);
				cout << auxPorto[i]->getChar();

				Consola::gotoxy(x + 1, y + 1);
				Consola::setTextColor(Consola::VERMELHO);
				cout << auxPorto[i]->getChar();
			}
			if (i % 2 != 0) {
				Consola::gotoxy(x, y);
				Consola::setTextColor(Consola::VERMELHO_CLARO);
				cout << auxPorto[i]->getChar();

				Consola::gotoxy(x + 1, y);
				Consola::setTextColor(Consola::VERMELHO_CLARO);
				cout << auxPorto[i]->getChar();

				Consola::gotoxy(x, y + 1);
				Consola::setTextColor(Consola::VERMELHO_CLARO);
				cout << auxPorto[i]->getChar();

				Consola::gotoxy(x + 1, y + 1);
				Consola::setTextColor(Consola::VERMELHO_CLARO);
				cout << auxPorto[i]->getChar();
			}
		}
	}

}
void Interface::mostraNavios() {

	const vector <const Navios *>  auxNavio = mundo.getVetorNavios();
	

	for (unsigned int i = 0; i < auxNavio.size(); i++) {

		unsigned int x = auxNavio[i]->getX();
		unsigned int y = auxNavio[i]->getY();

		x *= 2;
		y *= 2;

		if (i % 2 == 0) {

			if (auxNavio[i]->getEstado() == pirata) {
				Consola::gotoxy(x, y);
				Consola::setTextColor(Consola::VERMELHO_CLARO);
				cout << setfill('0') << setw(2) << auxNavio[i]->getId();

				Consola::gotoxy(x, y + 1);
				Consola::setTextColor(Consola::VERMELHO_CLARO);
				cout << setfill('0') << setw(2) << auxNavio[i]->getId();
			}
			if (auxNavio[i]->getEstado() == normal || auxNavio[i]->getEstado() == autoMove) {
					Consola::gotoxy(x, y);
					Consola::setTextColor(Consola::VERDE_CLARO);
					cout << setfill('0') << setw(2) << auxNavio[i]->getId();

					Consola::gotoxy(x, y + 1);
					Consola::setTextColor(Consola::VERDE_CLARO);
					cout << setfill('0') << setw(2) << auxNavio[i]->getId();
			}
			if(auxNavio[i]->getEstado() == aDeriva){
				Consola::gotoxy(x, y);
				Consola::setTextColor(Consola::BRANCO);
				cout << setfill('0') << setw(2) << auxNavio[i]->getId();

				Consola::gotoxy(x, y + 1);
				Consola::setTextColor(Consola::BRANCO);
				cout << setfill('0') << setw(2) << auxNavio[i]->getId();
			}
			if (auxNavio[i]->getEstado() == calmaria) {
				Consola::gotoxy(x, y);
				Consola::setTextColor(Consola::CYAN_CLARO);
				cout << setfill('0') << setw(2) << auxNavio[i]->getId();

				Consola::gotoxy(x, y + 1);
				Consola::setTextColor(Consola::CYAN_CLARO);
				cout << setfill('0') << setw(2) << auxNavio[i]->getId();
			}
		
		}
		if (i % 2 != 0) {

			if (auxNavio[i]->getEstado() == pirata) {
				Consola::gotoxy(x, y);
				Consola::setTextColor(Consola::VERMELHO_CLARO);
				cout << setfill('0') << setw(2) << auxNavio[i]->getId();

				Consola::gotoxy(x, y + 1);
				Consola::setTextColor(Consola::VERMELHO_CLARO);
				cout << setfill('0') << setw(2) << auxNavio[i]->getId();
			}
			if (auxNavio[i]->getEstado() == normal || auxNavio[i]->getEstado() == autoMove || auxNavio[i]->getEstado() == autoMove) {
				Consola::gotoxy(x, y);
				Consola::setTextColor(Consola::VERDE_CLARO);
				cout << setfill('0') << setw(2) << auxNavio[i]->getId();

				Consola::gotoxy(x, y + 1);
				Consola::setTextColor(Consola::VERDE_CLARO);
				cout << setfill('0') << setw(2) << auxNavio[i]->getId();
			}
			if (auxNavio[i]->getEstado() == aDeriva) {
				Consola::gotoxy(x, y);
				Consola::setTextColor(Consola::BRANCO);
				cout << setfill('0') << setw(2) << auxNavio[i]->getId();

				Consola::gotoxy(x, y + 1);
				Consola::setTextColor(Consola::BRANCO);
				cout << setfill('0') << setw(2) << auxNavio[i]->getId();
			}
			if (auxNavio[i]->getEstado() == calmaria) {
				Consola::gotoxy(x, y);
				Consola::setTextColor(Consola::CYAN_CLARO);
				cout << setfill('0') << setw(2) << auxNavio[i]->getId();

				Consola::gotoxy(x, y + 1);
				Consola::setTextColor(Consola::CYAN_CLARO);
				cout << setfill('0') << setw(2) << auxNavio[i]->getId();
			}
		}

	}
}
void Interface::mostraNaviosJogador() {

	const vector <const Navios *>  auxNavio = jogador.getVetorNaviosJogador();

	for (unsigned int i = 0; i < auxNavio.size(); i++) {

		unsigned int x = auxNavio[i]->getX();
		unsigned int y = auxNavio[i]->getY();
		Consola::gotoxy(45,28+i);
		cout << "Navio: " << i << "x:" << x << "y:" << y<<endl;
	}
}
void Interface::mostraMapa() {

	mostraSuperficie();
	mostraPortos();
	mostraNavios();
	mostraLegAndConfig();
};
Interface::~Interface()
{
}
