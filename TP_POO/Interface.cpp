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


string Interface::mostraInformacaoPortos() {

	ostringstream os;

	os << mundo.GetInformacaoPortos();

	os << "_________________________________________________________________" << endl;
	os << "_________________________________________________________________" << endl << endl;
	os << "<<<<	Precario :	>>>>" << endl;
	os << "Preco  do Navio : " << this->precoNavio << endl;
	os << "Preco  do Soldado : " << this->precoSoldado << endl;
	os << "Preco  da Venda de Peixe : " << this->precoVendePeixe << endl;
	os << "Preco  da Compra de Mercadoria : " << this->precoCompraMercadoria << endl;
	os << "Preco  da Venda de Mercadoria : " << this->precoVendaMercadoria << endl <<endl;
	os << "_________________________________________________________________" << endl << endl;

	return os.str();
}

string Interface::ExecutaEventos() {

	ostringstream os;


	if (this->InsercaoEvento != INSERCAO_COMANDO)
	 {

		if (mundo.getExistenciaEvento() == EVENTO_OFF) {

			//gotoErro();

			os << GeradorEvento(EVENTO_EXECUCAO_RAND, 0, 0, 0, 0);
		}
		else {

			if ( mundo.getExistenciaEvento() == EVENTO_ON){
		
			os << mundo.trataEventos(EVENTO_EXECUCAO_RAND,0,0,0,0);
			}
			else {
				mundo.setEventoEmExecucao(nullptr);
			}
		}
	}
	else
		this->InsercaoEvento = INSERCAO_RAND;

	return os.str();
}
string Interface::GeradorEvento(int ModoExecucao, int tipoEvento, int idNavio, int coordX, int coordY)
{
	ostringstream os;

	int op;
	
	while (mundo.getExistenciaEvento() != EVENTO_ON) {
			
		if (ModoExecucao != EVENTO_EXECUCAO_COMANDO)
			op = rand() % 4 + 1;
		else
			op = tipoEvento;
	
			switch (op)
			{
				case EVENTO_TEMPESTADE:
					if (ModoExecucao == EVENTO_EXECUCAO_COMANDO)
						os << mundo.trataEventos(ModoExecucao, tipoEvento, idNavio, coordX, coordY) << endl;
					else {
						if ((rand() % 100 + 1) <= this->probTempestade) {

							os << "Vai ser Gerada uma Tempestade " << endl;
						
						
						
							os << mundo.trataEventos(ModoExecucao, EVENTO_TEMPESTADE, idNavio,coordX, coordY) << endl;
					
						}
					}
					return os.str();
					
				break;
				case EVENTO_SEREIAS:
					if (ModoExecucao == EVENTO_EXECUCAO_COMANDO)
						os << mundo.trataEventos(ModoExecucao, tipoEvento, idNavio, coordX, coordY) << endl;
					else {

						if ((rand() % 100 + 1) <= this->probSereias) {

							os << " Vai ser Gerado um Ataque de Sereias " << endl;

							os << mundo.trataEventos(ModoExecucao, EVENTO_SEREIAS, idNavio, coordX, coordY) << endl;
						}
					}
					return os.str();
					
					break;
				case EVENTO_CALMARIA:
					if (ModoExecucao == EVENTO_EXECUCAO_COMANDO){

						os << mundo.criaEvento(&mundo, EVENTO_CALMARIA) << endl;

						os << mundo.trataEventos(ModoExecucao, tipoEvento, idNavio, coordX, coordY);
					
					} else {

						if ((rand() % 100 + 1) <= this->probCalmaria) {

							os << "Vai ser Gerado um Evento Calmaria " << endl;
					
							os << mundo.criaEvento(&mundo, EVENTO_CALMARIA) << endl;
						
							os << mundo.trataEventos(ModoExecucao, tipoEvento, idNavio, coordX, coordY);
						}
					}
					return os.str();

					break;

				case EVENTO_MOTIM:

					if (mundo.VerificaExistenciaNavios() == true) {

						if (ModoExecucao != EVENTO_EXECUCAO_COMANDO) {

							if ((rand() % 100 + 1) <= this->probMotin) {

									os << "Vai ser Gerado um Evento Motim " << endl;

									os << mundo.criaEvento(&mundo, EVENTO_MOTIM) << endl;

									os << mundo.trataEventos(ModoExecucao, tipoEvento, idNavio, coordX, coordY);
							
							}
						}
						else {

								os << "Vai ser Gerado um Evento Motim " << endl;

								os << mundo.criaEvento(&mundo, EVENTO_MOTIM) << endl;

								os << mundo.trataEventos(ModoExecucao, tipoEvento, idNavio, coordX, coordY);

							}
					}
					else
						os << "Nao existem navios no Mundo para efetuar o Evento Motim" << endl;

					return os.str();

					break;
			}
		}
	return os.str();
}
void Interface::criaPiratasAuto() {

	unsigned int aux = 10,aux2=0;
	unsigned int x = 0, y = 0;

	//vai criar pirata consoante a sua probabilidade
	if ((rand() % 100 + 1) <= probPirata) {

		//gerar o x e  o y
		do {

			x = rand() % mundo.getDimX();
			y = rand() % mundo.getDimY();

			if (mundo.verificaCelulaMar(x, y) == CELULA_MAR && mundo.verificaCelulaNavio(x, y) != CELULA_NAVIO) {
				break;
			}
			aux--;
		} while (aux > 0);

		//que tipo de pirata vai criar
		aux2 = (rand() % 2);
		if (aux2 == 0)
			mundo.criaNavPirata(&mundo, 'F', x, y);
		if (aux2 == 1) 
			mundo.criaNavPirata(&mundo, 'V', x, y);
		
	}
}
void Interface::criaNaviosJogador() {

	unsigned int aux = 10, aux2 = 0;
	unsigned int x = 0, y = 0;

	//vai criar pirata consoante a sua probabilidade
	if ((rand() % 100 + 1) <= 60) {

		//gerar o x e  o y
		do {

			x = rand() % mundo.getDimX();
			y = rand() % mundo.getDimY();

			if (mundo.verificaCelulaMar(x, y) == CELULA_MAR && mundo.verificaCelulaNavio(x, y) != CELULA_NAVIO) {
				break;
			}
			aux--;
		} while (aux > 0);

		//que tipo de pirata vai criar
		aux2 = (rand() % 2);
		if (aux2 == 0)
			jogador.addNavioJogador(&mundo.criaNavio(&mundo, jogador.getPortoPrincipal(), 'F'));
		if (aux2 == 1)
			jogador.addNavioJogador(&mundo.criaNavio(&mundo, jogador.getPortoPrincipal(), 'V'));

	}
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

bool Interface::verificaLeComandos(string aux) {
		
	istringstream buffer(aux);
	istringstream buffer2(aux);

	string acao;
	string nomeFich;
	string linha;
	char tipo;
	int idNavio;
	int nMercadoria;
	char direcao;
	int x, y;
	int nSoldados;
	

	if (buffer >> acao) {
		switch (FiltaComandos(acao)) {
		case com_exec:
			//verifica se o ficheiro existe
			return true;
			break;
			//############################################################################################################################################
		case com_prox:
			return true;
			break;
			//############################################################################################################################################
		case com_compranav:
			buffer >> tipo;
			if (tipo == 'V' || tipo == 'G' || tipo == 'E' || tipo == 'F' || tipo == 'T' || tipo == 'S' && count(aux.begin(), aux.end(), ' ') == 1) {
				return true;
			}
			else
				return false;
			break;
			//############################################################################################################################################
		case com_vendenav:
			if (buffer >> tipo) {
				return true;
			}
			else
				return false;
			break;
			//############################################################################################################################################
		case com_lista:
			return true;
			break;
			//############################################################################################################################################
		case com_compra:
			if (buffer >> idNavio && buffer >> nMercadoria && count(aux.begin(), aux.end(), ' ') == 2) {
				return true;
			}
			else
				return false;
				break;
				//############################################################################################################################################
		case com_vende:
			if (buffer >> idNavio && count(aux.begin(), aux.end(), ' ') == 1) {
				return true;
			}
			else
				return false;
			break;
			//############################################################################################################################################
		case com_move:
			if (buffer >> idNavio && buffer >> direcao && count(aux.begin(), aux.end(), ' ') == 2) {
				return true;
			}
			else
				return false;
			break;
			//############################################################################################################################################
		case com_auto:
			if (buffer >> idNavio && count(aux.begin(), aux.end(), ' ') == 1) {
				return true;
			}
			else
				return false;
			break;
			//############################################################################################################################################
		case com_stop:
			if (buffer >> idNavio && count(aux.begin(), aux.end(), ' ') == 1) {
				return true;
			}
			else
				return false;
			break;
			//############################################################################################################################################
		case com_pirata:
			if (buffer >> tipo && buffer >> x && buffer >> y && count(aux.begin(), aux.end(), ' ') == 3) {
				if (tipo == 'V' || tipo == 'F') {
					return true;
				}
				return false;
			}
			break;
			//############################################################################################################################################
		case com_evpos:
			if (buffer >> tipo && buffer >> x && buffer >> y && count(aux.begin(), aux.end(), ' ') == 3) {
				return true;
			}
			else
				return false;
			break;
			//############################################################################################################################################
		case com_evnav:
			if (buffer >> tipo && buffer >> idNavio && count(aux.begin(), aux.end(), ' ') == 2) {
				return true;
			}
			else
				return false;
			break;
			//############################################################################################################################################
		case com_moedas:
			if (buffer >> idNavio) {
				return true;
			}
			else
				return false;
			break;
			//############################################################################################################################################
		case com_vaipara:
			//este comando tem overload devido aos parametros vaipara <N> <x> <y> e vai para <N> <P>

			if (buffer >> idNavio && buffer >> tipo) {

				if ((tipo >= 'A' && tipo <= 'Z') || (tipo >= 'a' && tipo <= 'z')) {
					return true;
				}
				else
					if (buffer2 >> acao && buffer2 >> idNavio && buffer2 >> x && buffer2 >> y) {
						return true;
					}
					else
						return false;
			}
			else
				return false;
			break;
			//############################################################################################################################################
		case com_comprasold:
			if (buffer >> idNavio && buffer >> nSoldados && count(aux.begin(), aux.end(), ' ') == 2) {
				return true;
			}
			else
				return false;
			break;
			//############################################################################################################################################
		case com_saveg:
			return true;
			break;
			//############################################################################################################################################
		case com_loadg:
			return true;
			break;
			//############################################################################################################################################
		case com_delg:
			return true;
			break;
			//############################################################################################################################################
		case com_sair:
				return true;
		}
	}
	return false;
}
vector <string> Interface::leComandos() {


	vector <string> vetordComandos;

	string aux;

	do {

		getline(cin, aux);


		if (verificaLeComandos(aux) == true) {//se o comando introduzido na sequencia for correto
			vetordComandos.push_back(aux);
		}
		else {
			/*gotoErro();
			cout << "comando: " << aux << " incorreto" << endl;*/
		}
	} while (aux != "prox");


	return vetordComandos;
}
int Interface::verificaExec(vector <string> comandExec) {

	
	string palavra;
	
	for (unsigned int i = 0; i < comandExec.size(); i++) {

		istringstream comando(comandExec[i]);
		comando >> palavra;
		if (palavra == "exec") {
			return i;
		}
	}
	return -1;
}
string Interface::leFich(string nomeFich) {

	ostringstream os;

	vector <string> vetordComandos;
	fstream fp;
	string linha;


	if (!fp.is_open()) {

		fp.open(nomeFich);

		while (getline(fp, linha)) {

			if (verificaLeComandos(linha) == true) {
				vetordComandos.push_back(linha);
			}
		}

		fp.close();
			os << "________OUTPUT_DOS_COMANDOS_DO_FICHEIRO____________ " << endl;
		for (unsigned int i = 0; i < vetordComandos.size(); i++) {

			os << PromptFase2(vetordComandos[i]);

		}
		os << "_______________________________________________________ " << endl;
	}
	else{

		os << "________NAO_FOI_POSSIVEL_ABRIR_O_____________ " << endl;
	}

	return os.str();
}
string Interface::mostraStatusNavio() {

	ostringstream os;

	os << mundo.mostraStatusNavio();

	return os.str();

}

// Metodo Prompt tem como objetivo tratar os comandos introduzidos pelo Jogador	
void Interface::Prompt() {

	string linha, acao, configFile;
	int proxComando = 0;
	ostringstream os;

	Consola::VERDE;
	vector <string> vectorComandos;
	gotoComando();
	cout << "Comando: config ";

	getline(cin, linha);

	/*
	______________________________________________________________________________________

					iniciar a fase 1: trata comando config
	______________________________________________________________________________________
	*/
	PromptFase1(linha);
	Consola::clrscr();
	mostraMapa();


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
		/////////////////////////////////////////////////////////////////////

		proxComando = 0;
		vectorComandos.erase(vectorComandos.begin(), vectorComandos.end());

		gotoComando();
		cout << "Comando: "<<endl;
		vectorComandos = leComandos();
		
		
		
		int indiceExec = verificaExec(vectorComandos);
		 

		Consola::clrscr();

		do {

			if (indiceExec >= 0) {
				
				os << leFich( vectorComandos[indiceExec].substr(vectorComandos[indiceExec].find_first_of(' ') + 1, vectorComandos[indiceExec].size()) );
				indiceExec = -1;
			}

			os << PromptFase2(vectorComandos[proxComando]);
			if (vectorComandos[proxComando] != "prox") {
				proxComando++;
			}
		} while (vectorComandos[proxComando] != "prox");

		////////////////////////////////////////////////////////////////////

		if (verificaFimdoJogo() == 1) {
			Sleep(4000);
			return;
		}

		mundo.retiraNavAfundados();
		//criaNaviosJogador(); //apagar isto daqui
		criaPiratasAuto();
		cout << mundo.mandaVaiPara(this->precoVendaMercadoria, this->precoVendePeixe);
		jogador.setPortoPrincipal(mundo.getPortoPrincipal());
		mundo.abasteceNaviosNosPortos();
		cout << jogador.moveNavioAuto(this->Turno);
		cout << mundo.moveNavioPirataAuto(this->Turno);
		mundo.verificaaDeriva();
		mundo.VerificaRegeneracaoPeixeMar(this->Turno);
		jogador.adicionaMoedas(mundo.EsvaziaBancoJogador());
		cout << ExecutaEventos();
		Consola::clrscr();
		mostraMapa();
		Consola::gotoxy(0,50);
		cout << os.str();
		
		os.str("");
		Consola::gotoxy(0, 0);
		this->Turno = this->incTurno++;
		cout << "Turno : " << this->Turno;
		cout << "_______________________________________________________________________________________" << endl;

	} while (vectorComandos[proxComando]!="sair");


}




int Interface::FiltaComandos(string acao) {

	vector< string > comandos = {"exec", "prox", "compranav", "vendenav", "lista", "compra", "vende", "move", "auto", "stop", "pirata","evpos","evnav",
								  "moedas", "vaipara", "comprasold", "saveg", "loadg", "delg","sair"};

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
	//mundo.setQuantidadeSoldadosPortos(this->soldadosPorto);
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
				case probpeixe:
					this->probPeixe = inteiro;
					break;
			}
		}
		else {
			buffer >> linha;
			for (int i = 0; i < mundo.getDimX(); i++) {
				if (linha[i] == '.') {

					this->mundo.criaSuperficie(i, contaColunas, linha[i], this->probPeixe);
				}
				if (linha[i] == '+') {

					this->mundo.criaSuperficie(i, contaColunas, linha[i]);
				}
				if (linha[i] >= 'A' && linha[i] <= 'Z' || linha[i] >= 'a' && linha[i] <= 'z') {
		
					this->mundo.criaCelulaPorto(i, contaColunas,linha[i], this->soldadosPorto );

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
	case 'T':
		if (jogador.validaCompra(PRECO_TARTARUGA)) {
			jogador.setMoedas((jogador.getMoedas() - PRECO_TARTARUGA));
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
string Interface::PromptFase2(string linha) {

	char tipo;
	string acao, direcao;
	int idNavio,x,y, nSoldados, nMercadoria;
	istringstream buffer(linha);
	istringstream buffer2(linha);
	ostringstream os;
	
	if (buffer >> acao) {
		switch (FiltaComandos(acao)) {
		case com_exec:
			break;
		case com_prox:
			break;
		case com_compranav:
			buffer >> tipo;
			if (tipo == 'V' || tipo == 'G' || tipo == 'E' || tipo == 'F' || tipo == 'T' || tipo == 'S' && count(linha.begin(), linha.end(), ' ') == 1) {

				if (compraNavio(tipo) == COMPRA_COM_SUCESSO) {
					os << "Compra efetuada com sucesso!" << endl;
				}
				else if (compraNavio(tipo) == COMPRA_SEM_MOEDAS) {
					os << "Compra n�o efetuada <-> Jogador Sem Moedas" << endl;
				}
				else if ((compraNavio(tipo) == TIPO_NAVIO_INVALIDO)) {
					os << "Compra nao efetuada <-> N�o existe porto principal" << endl;
				}
			}
			else {
				os << " [ Sintaxe " << acao << " Invalida..! Sintaxe :" << acao << " <N> ]" << endl;
			}
			
			os << "Saldo atual do Jogador: " << jogador.getMoedas() << endl;
			break;
		case com_vendenav:
			if (buffer >> tipo) {
				acrescentaMoedas(jogador.vendeNavio(tipo, precoSoldado));
			}
			break;
		case com_lista:
			
			os << mostraInformacaoPortos();
			break;
		case com_compra:
			if (buffer >> idNavio && buffer >> nMercadoria && count(linha.begin(), linha.end(), ' ') == 2) {
				if (jogador.validaIdNavio(idNavio)) {
					Navios *auxNavio = jogador.getNavio(idNavio);
					if (auxNavio != nullptr) {
						Porto *auxPorto = mundo.getPorto(auxNavio->getX(), auxNavio->getY());
						if (auxPorto != nullptr) {
							if (auxPorto->getMercadoria() - nMercadoria >= 0 && jogador.getMoedas() - (nMercadoria*this->precoCompraMercadoria) >= 0) {
								/*cout << "quantidade de Mercadoria a Comprar " << nMercadoria << endl;
								cout << "_______________________________________________________________________" << endl;
								cout << " Quantidade de Mercadoria no Navio " << auxNavio->getMercadoriaNavio() << endl;
								cout << " Quantidade de Mercadoria no Porto " << auxPorto->getMercadoria() << endl;
								cout << " Quantidade de moedas do jogador " << jogador.getMoedas() << endl;*/
								if (nMercadoria + auxNavio->getMercadoriaNavio() <= auxNavio->VerificaMaxMercadoria()) {
									auxNavio->adicionaMercadoriaNavio(nMercadoria);
									auxPorto->setMercadoria(auxPorto->getMercadoria() - nMercadoria);
									jogador.setMoedas(jogador.getMoedas() - (nMercadoria*this->precoCompraMercadoria));
								}
								else{
									os << " O Navio encontra-se carregado nao tendo capacidade para Comprar mais Mercadoria \n ou" << endl;
								}
								/*cout << "_______________________________________________________________________"<< endl;
								cout << " Quantidade de Mercadoria no Navio" << auxNavio->getMercadoriaNavio() << endl;
								cout << " Quantidade de Mercadoria no Porto " << auxPorto->getMercadoria() << endl;
								cout << " Quantidade de moedas do jogador " << jogador.getMoedas() << endl;*/
							}
							else {
								os << "Quantidade de mercadoria a ComPrar Superior a que o Porto tem para vender " << endl;
								os << "ou \n Quantidade de moedas do jogador insuficiente" << endl;

							}
						}
						else {
							os << " [ Erro..! O Navio Com o Id : " << idNavio << "  nao se encontra em nenhum Porto Amigo" << endl;
						}
					}
				}
				else {
					os << " [ Erro..! O Navio Com o Id : " << idNavio << "  nao existe.. !" << endl;
				}
			}
			else {
				os << " [ Erro..! o comando introduzido esta incorrecto... Sitaxe: compra <ID_N> <M>  ]" << endl;
			}
			break;
		case com_vende:
			if (buffer >> idNavio && count(linha.begin(), linha.end(), ' ') == 1) {
				if (jogador.validaIdNavio(idNavio)) {
					Navios *auxNavio = jogador.getNavio(idNavio);
					if (auxNavio != nullptr) {
						Porto *auxPorto = mundo.getPorto(auxNavio->getX(), auxNavio->getY());
						if (auxPorto != nullptr) {
							if (auxNavio->getMercadoriaNavio() > 0) {
								/*cout << "_____________________________________________________________________________" << endl;
								cout << " Quantidade de Mercadoria no Navio " << auxNavio->getMercadoriaNavio() << endl;
								cout << " Quantidade de Mercadoria no Porto " << auxPorto->getMercadoria() << endl;
								cout << " Quantidade de moedas do jogador " << jogador.getMoedas() << endl;*/
								jogador.setMoedas(jogador.getMoedas() + auxNavio->getMercadoriaNavio() * this->precoVendaMercadoria);
								auxPorto->setMercadoria(auxPorto->getMercadoria() + auxNavio->getMercadoriaNavio());
								auxNavio->setMercadoriaNavio(0);
								/*cout << "_____________________________________________________________________________" << endl;
								cout << " Quantidade de Mercadoria no Navio " << auxNavio->getMercadoriaNavio() << endl;
								cout << " Quantidade de Mercadoria no Porto " << auxPorto->getMercadoria() << endl;
								cout << "Quantidade de moedas do jogador " << jogador.getMoedas() << endl;*/	
							}
							else {
								os << "[ Erro .. ! O navio com o Id : " << idNavio << " nao tem Carga para vender" << endl;
							}
						}
						else {
							os << " [ Erro..! O Navio Com o Id : " << idNavio << "  nao se encontra em nenhum Porto Amigo" << endl;
						}
					}
				}
				else {
					os << " [ Erro..! O Navio Com o Id : " << idNavio << "  nao existe.. !" << endl;
				}
			}
			else {
				os << " [ Erro..! o comando introduzido esta incorrecto... Sitaxe: compra <ID_N> <M>  ]" << endl;
			}
			break;
		case com_move:
			if (buffer >> idNavio && buffer >> direcao && count(linha.begin(), linha.end(), ' ') == 2) {
				Navios *auxNavio=nullptr;
				if (ValidaDirecoes(direcao))
					if (jogador.validaIdNavio(idNavio) == true)
						if (!jogador.verificaModoAutomaticoNavio(idNavio)) {
							auxNavio = mundo.getNavio(idNavio);
							if( auxNavio->getEstado() != calmaria && auxNavio->getEstado() != motim){
								jogador.moveNavioJogador(idNavio, ValidaDirecoes(direcao), this->Turno);//com sucesso
									os << auxNavio->combate(CELULA_NAVIO_PIRATA);
							}
						} 
						else
							os << "[ Erro..! AutoMove do Navio : " << idNavio << " esta ativo ..! ]" << endl;
					else
						os << "[ Erro..! Id : " << idNavio << " de Navio Invalido ..! ]" << endl;
				else 
					os << "[ Erro..! Direcao : " << direcao << " de Navio Invalido ..! ]" << endl;
			}
			else {
				os << " [ Sintaxe " << acao << "Invalida..! Use" << acao << "<N> <X> || nota: X = C,B,D,E,CE,CD,BE,BD ]" << endl;
			}
			break;
		case com_auto:
			if (buffer >> idNavio && count(linha.begin(), linha.end(), ' ') == 1) {
				if (jogador.validaIdNavio(idNavio)) 
					jogador.AlteraAutoMoveNavio(idNavio, autoMove);
				else {
					os << "[ Id introduzido: " << idNavio << " invalido  ]" << endl;
				}
			}
			else {
				os << "[ COMANDO : " << acao << " ainda nao Implementado ] " << endl;
			}
			break;
		case com_stop:
			if (buffer >> idNavio && count(linha.begin(), linha.end(), ' ') == 1) {
				if (jogador.validaIdNavio(idNavio) == true)
					jogador.AlteraAutoMoveNavio(idNavio, normal);
			}
			else {
				os << " [ Erro..! o comando introduzido est� incorrecto... Sitaxe: stop <ID_N>  ]" << endl;
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
	
		if (mundo.getExistenciaEvento() == EVENTO_OFF) {

			if (buffer >> tipo && buffer >> x && buffer >> y && count(linha.begin(), linha.end(), ' ') == 3) {

				this->InsercaoEvento = INSERCAO_COMANDO;

				if (tipo == 'T')
					os << GeradorEvento(EVENTO_EXECUCAO_COMANDO, EVENTO_TEMPESTADE,0, x, y);
				else if (tipo == 'C')
					os << GeradorEvento(EVENTO_EXECUCAO_COMANDO, EVENTO_CALMARIA,0, x, y);

				
			}
		}
		else
			os << "existe um evento a decorrer..." << endl;
	
		break;

	case com_evnav:
	
		if (mundo.getExistenciaEvento() == EVENTO_OFF) {

			if (buffer >> tipo && buffer >> idNavio && count(linha.begin(), linha.end(), ' ') == 2) {
				
				this->InsercaoEvento = INSERCAO_COMANDO;

				if (tipo == 'M')
					os << GeradorEvento(EVENTO_EXECUCAO_COMANDO, EVENTO_MOTIM, idNavio, 0, 0);
				else if (tipo == 'S')
					os << GeradorEvento(EVENTO_EXECUCAO_COMANDO, EVENTO_SEREIAS, idNavio, 0, 0);
			}
		}
		else
			os << "existe um evento a decorrer..." << endl;
		
		break;
	case com_moedas:
		
		if (buffer >> idNavio) {
			acrescentaMoedas(idNavio);// neste caso idNavio � o nr de moedas que o jogador introduziu
		}
		break;
	case com_vaipara:
		//este comando tem overload devido aos parametros vaipara <N> <x> <y> e vai para <N> <P>
	
		if (buffer >> idNavio && buffer >> tipo) {
		
			if ((tipo >= 'A' && tipo <= 'Z') || (tipo >= 'a' && tipo <= 'z')) {
				mundo.setVaiPara(idNavio, tipo);
			}else
				if (buffer2 >> acao && buffer2 >> idNavio && buffer2 >> x && buffer2 >> y) {
					mundo.setVaiPara(idNavio, x, y);
				}
		}

		break;
	case com_comprasold:

		if (buffer >> idNavio && buffer >> nSoldados && count(linha.begin(), linha.end(), ' ') == 2) {
			if (jogador.validaIdNavio(idNavio)) {
				Navios *auxNavio  = jogador.getNavio(idNavio);
				if (auxNavio != nullptr){
					Porto *auxPorto = mundo.getPorto(auxNavio->getX(), auxNavio->getY());
					if (auxPorto != nullptr) {
						if ( auxPorto->getNumSoldados() >= nSoldados){
				/*		cout << "_____________________________________________________________________________" << endl;
							cout << " Quantidade de Soldados no Navio " << auxNavio->getNumSoldados() << endl;
							cout << " Quantidade de Soldados no Porto " << auxPorto->getNumSoldados() << endl;
							cout << " Quantidade de moedas do jogador " << jogador.getMoedas() << endl;
*/
							if ((nSoldados + auxNavio->getNumSoldados()) > auxNavio->getMaxSoldados()) {
								auxPorto->setNumSoldados(auxPorto->getNumSoldados() - (auxNavio->getMaxSoldados() - auxNavio->getNumSoldados()));
								auxNavio->setNumSoldados(auxNavio->getMaxSoldados());	
								jogador.setMoedas(jogador.getMoedas() - (this->precoSoldado*(auxNavio->getMaxSoldados() - auxNavio->getNumSoldados())));
							}
							else{
						
								auxPorto->setNumSoldados(auxPorto->getNumSoldados() - nSoldados);
								auxNavio->setNumSoldados(auxNavio->getNumSoldados() + nSoldados);
								jogador.setMoedas(jogador.getMoedas() - (this->precoSoldado * nSoldados));
							}
					/*		cout << "_____________________________________________________________________________" << endl;
							cout << " Quantidade de Soldados no Navio " << auxNavio->getNumSoldados() << endl;
							cout << " Quantidade de Soldados no Porto " << auxPorto->getNumSoldados() << endl;
							cout << " Quantidade de moedas do jogador " << jogador.getMoedas() << endl;*/
						}

						else{
							os<< "quantidade de soldados a Comprar e superior aos Soldados existentes no Porto" << endl;
						}
					}
					else {
						os << " [ Erro..! O Navio Com o Id : " << idNavio << "  nao se encontra em nenhum Porto Amigo" << endl;
					}
				}
			}
			else {
				os << " [ Erro..! O Navio Com o Id : " << idNavio << "  nao existe.. !" << endl;
			}
		}
		else {
			os << " [ Erro..! o comando introduzido esta incorrecto... Sitaxe: comprasold <ID_N> <S>  ]" << endl;
		}
		break;
	case com_saveg:
		os << "[ COMANDO : " << acao << " ainda nao Implementado ] " << endl;
		break;
	case com_loadg:
		os << "[ COMANDO : " << acao << " ainda nao Implementado ] " << endl;
		break;
	case com_delg:
		os << "[ COMANDO : " << acao << " ainda nao Implementado ] " << endl;
		break;
	default:
		if (acao != "sair") {
			os << " [ ERRO..! Comando Incorreto..!  ]" << endl;
		}
	}
}
return os.str();
}

bool Interface::getInsercaoComandoEvento() const
{
	return this->InsercaoEvento;
}

void Interface::setInsercaoComandoEvento(bool insercao)
{
	this->InsercaoEvento = insercao;
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
	Consola::gotoxy(87, 16);
	cout << "Probabilidade Peixe " << this->probPeixe;

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
				if (auxSuperficie[i]->VerificaCardumePeixe() == PEIXE_ON) {
					Consola::setTextColor(Consola::CINZENTO);
					cout << char(190);
					}
				else
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
				if (auxSuperficie[i]->VerificaCardumePeixe() == PEIXE_ON) {
	
					Consola::setTextColor(Consola::CINZENTO);
					cout << char(190);
				}
				else
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
				cout << setfill('0') << setw(2) << auxNavio[i]->getTipo();
			}
			if (auxNavio[i]->getEstado() == normal || auxNavio[i]->getEstado() == autoMove || auxNavio[i]->getEstado() == vaiPara) {
					
				Consola::gotoxy(x, y);
					Consola::setTextColor(Consola::VERDE_CLARO);
					cout << setfill('0') << setw(2) << auxNavio[i]->getId();

					Consola::gotoxy(x, y + 1);
					Consola::setTextColor(Consola::VERDE_CLARO);
					cout << setfill('0') << setw(2) << auxNavio[i]->getTipo();
					
					if (auxNavio[i]->sou() == TARTARUGA) {
						Consola::gotoxy(x, y);
						Consola::setTextColor(Consola::COR_DE_ROSA);
						cout << setfill('0') << setw(2) << auxNavio[i]->getId();

						Consola::gotoxy(x, y + 1);
						Consola::setTextColor(Consola::COR_DE_ROSA);
						cout << setfill('0') << setw(2) << auxNavio[i]->getTipo();
					}
			}
			if(auxNavio[i]->getEstado() == aDeriva){
				Consola::gotoxy(x, y);
				Consola::setTextColor(Consola::BRANCO);
				cout << setfill('0') << setw(2) << auxNavio[i]->getId();

				Consola::gotoxy(x, y + 1);
				Consola::setTextColor(Consola::BRANCO);
				cout << setfill('D') << setw(2) << auxNavio[i]->getTipo();
			}
			if (auxNavio[i]->getEstado() == calmaria) {
				Consola::gotoxy(x, y);
				Consola::setTextColor(Consola::CYAN_CLARO);
				cout << setfill('0') << setw(2) << auxNavio[i]->getId();

				Consola::gotoxy(x, y + 1);
				Consola::setTextColor(Consola::CYAN_CLARO);
				cout << setfill('C') << setw(2) << auxNavio[i]->getTipo();
			}
		
		}
		if (i % 2 != 0) {

			if (auxNavio[i]->getEstado() == pirata) {
				Consola::gotoxy(x, y);
				Consola::setTextColor(Consola::VERMELHO_CLARO);
				cout << setfill('0') << setw(2) << auxNavio[i]->getId();

				Consola::gotoxy(x, y + 1);
				Consola::setTextColor(Consola::VERMELHO_CLARO);
				cout << setfill('0') << setw(2) << auxNavio[i]->getTipo();
			}
			if (auxNavio[i]->getEstado() == normal || auxNavio[i]->getEstado() == autoMove || auxNavio[i]->getEstado() == autoMove || auxNavio[i]->getEstado() == vaiPara) {
				Consola::gotoxy(x, y);
				Consola::setTextColor(Consola::VERDE_CLARO);
				cout << setfill('0') << setw(2) << auxNavio[i]->getId();

				Consola::gotoxy(x, y + 1);
				Consola::setTextColor(Consola::VERDE_CLARO);
				cout << setfill('0') << setw(2) << auxNavio[i]->getTipo();
				if (auxNavio[i]->sou() == TARTARUGA) {
					Consola::gotoxy(x, y);
					Consola::setTextColor(Consola::COR_DE_ROSA);
					cout << setfill('0') << setw(2) << auxNavio[i]->getId();

					Consola::gotoxy(x, y + 1);
					Consola::setTextColor(Consola::COR_DE_ROSA);
					cout << setfill('0') << setw(2) << auxNavio[i]->getTipo();
				}
			}
			if (auxNavio[i]->getEstado() == aDeriva) {
				Consola::gotoxy(x, y);
				Consola::setTextColor(Consola::BRANCO);
				cout << setfill('0') << setw(2) << auxNavio[i]->getId();

				Consola::gotoxy(x, y + 1);
				Consola::setTextColor(Consola::BRANCO);
				cout << setfill('D') << setw(2) << auxNavio[i]->getTipo();
			}
			if (auxNavio[i]->getEstado() == calmaria) {
				Consola::gotoxy(x, y);
				Consola::setTextColor(Consola::CYAN_CLARO);
				cout << setfill('0') << setw(2) << auxNavio[i]->getId();

				Consola::gotoxy(x, y + 1);
				Consola::setTextColor(Consola::CYAN_CLARO);
				cout << setfill('C') << setw(2) << auxNavio[i]->getTipo();
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
