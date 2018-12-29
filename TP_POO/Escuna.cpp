#include "Escuna.h"
#include "Mundo.h"

void Escuna::AbasteceAguaNavio()
{
	this->quantAgua = ESCUNA_MAX_AGUA;
}
const int Escuna::sou()const {
	return ESCUNA;
}
int Escuna::getMaxAgua() {
	return ESCUNA_MAX_AGUA;
}
int Escuna::getAgua() {
	return this->quantAgua;
}
void Escuna::adicionaAgua(int agua) {
	this->quantAgua += agua;
}
void Escuna::retiraAgua(int agua) {

	this->quantAgua -= agua;

}
int Escuna::getMaxSoldados() {
	return ESCUNA_MAX_SOLDADOS;
}
void Escuna::retiraSoldados(int soldados) {

	this->quantSoldados -= soldados;

}
void Escuna::daMetade(int x, int y) {

	Navios *auxNavio = nullptr;
	auxNavio = mundo->getNavioXY(x, y);
	if (auxNavio->getNumSoldados() > 0) {
		//fico com metade para mim  soldados e agua
		this->quantAgua = auxNavio->getAgua() / 2;
		this->quantSoldados = auxNavio->getNumSoldados() / 2;
		//tira metade ao que da soldados e agua
		auxNavio->retiraAgua(auxNavio->getAgua() / 2);
		auxNavio->retiraSoldados(auxNavio->getNumSoldados() / 2);
	}
	else
		this->estado = aDeriva;
}
void Escuna::serConquistadoaDeriva() {

	int x = this->x, y = this->y;
	switch (mundo->verificaCelulaNavioPirata(x + 1, y)) {
	case CELULA_NAVIO_NORMAL:
		this->estado = autoMove;
		daMetade(x + 1, y);
		break;
	case CELULA_NAVIO_PIRATA:
			this -> estado = afundado;
		break;
	default:
		break;
	}
	switch (mundo->verificaCelulaNavioPirata(x - 1, y)) {
	case CELULA_NAVIO_NORMAL:
		this->estado = autoMove;
		daMetade(x - 1, y);
		break;
	case CELULA_NAVIO_PIRATA:
		this->estado = afundado;
		break;
	default:
		break;
	}
	switch (mundo->verificaCelulaNavioPirata(x, y - 1)) {
	case CELULA_NAVIO_NORMAL:
		this->estado = autoMove;
		daMetade(x, y - 1);
		break;
	case CELULA_NAVIO_PIRATA:
		this->estado = afundado;
		break;
	default:
		break;
	}
	switch (mundo->verificaCelulaNavioPirata(x, y + 1)) {
	case CELULA_NAVIO_NORMAL:
		this->estado = autoMove;
		daMetade(x, y + 1);
		break;
	case CELULA_NAVIO_PIRATA:
		this->estado = afundado;
		break;
	default:
		break;
	}
	switch (mundo->verificaCelulaNavioPirata(x + 1, y - 1)) {
	case CELULA_NAVIO_NORMAL:
		this->estado = autoMove;
		daMetade(x + 1, y - 1);
		break;
	case CELULA_NAVIO_PIRATA:
		this->estado = afundado;
		break;
	default:
		break;
	}
	switch (mundo->verificaCelulaNavioPirata(x - 1, y - 1)) {
	case CELULA_NAVIO_NORMAL:
		this->estado = autoMove;
		daMetade(x - 1, y - 1);
		break;
	case CELULA_NAVIO_PIRATA:
		this->estado = afundado;
		break;
	default:
		break;
	}
	switch (mundo->verificaCelulaNavioPirata(x + 1, y + 1)) {
	case CELULA_NAVIO_NORMAL:
		this->estado = autoMove;
		daMetade(x + 1, y + 1);
		break;
	case CELULA_NAVIO_PIRATA:
		this->estado = afundado;
		break;
	default:
		break;
	}
	switch (mundo->verificaCelulaNavioPirata(x - 1, y + 1)) {
	case CELULA_NAVIO_NORMAL:
		this->estado = autoMove;
		daMetade(x - 1, y + 1);
		break;
	case CELULA_NAVIO_PIRATA:
		this->estado = afundado;
		break;
	default:
		break;
	}

}
string Escuna::moveNavioAuto(int turnoAtual) {

	ostringstream os;
	
		if (this->estado == autoMove || this->estado == aDeriva) {

			unsigned int direcao;

			direcao = mundo->VerificaCelulaCardumePeixe(this->x, this->y);

			if ( direcao == 0)
				direcao = rand() % 9 + 1;

			this->moveNavio(direcao, turnoAtual);
			
			if (this->estado == autoMove) {
				this->soldadosBebemAgua();
				os<<this->combate(CELULA_NAVIO_PIRATA);
			}
		}
		return os.str();
}
void Escuna::soldadosBebemAgua() {
	
	if(mundo->verificaCelulaMar(this->x,this->y) || (mundo->verificaCelulaPorto(this->x, this->y) !=CELULA_PORTO_AMIGO)){
		if(this->quantAgua>0)
			this->quantAgua -= this->getNumSoldados();
	}
	if (this->quantAgua <= 0) {
		if (this->quantSoldados > 0) {
			this->quantSoldados -= 1;
		}
		if (this->quantSoldados <= 0){
			this->estado = aDeriva;
		}
	}
}
string Escuna::combate(int quemVouAtacar) { //vai para o porto quando n tem agua
	ostringstream os;

	const vector <const Porto *>  auxPorto = mundo->getVetorPorto();

	if (this->getAgua() <= this->getMaxAgua() / 4) {

		for (unsigned int i = 0; i < auxPorto.size(); i++) {
			if (auxPorto[i]->getChar() >= 'A' && auxPorto[i]->getChar() <= 'Z') {
				mundo->setVaiPara(this->getId(), auxPorto[i]->getChar());
				break;
			}
			else
				this->setEstado(autoMove);

		}

	}


	return os.str();
}
int Escuna::FmoveEsquerda(int turnoJogo) {


	// Aqui vai verificar se vai existir peixe na celula 
	Superficie *auxMar = mundo->VerificaExistenciaPeixe(this->x - 1, this->y);
	
	if (this->estado == autoMove || this->estado == normal) {
		
		if (auxMar != nullptr  && this->QuantMercadoria + 1 <= ESCUNA_QUANT_MAX_CARGA) {

			this->QuantPeixe = this->QuantPeixe + PEIXE_PESCADO;

			this->QuantMercadoria = this->QuantMercadoria + PEIXE_PESCADO;

			auxMar->PescaCardumeMar(turnoJogo);
			cout << "Turno em que o peixe foi pescado " << auxMar->getTurno() << endl;

		}
	}
	int VerificaPorto = 0;
	//e ver se a nova pos est� dentro de agua!
	if (x > 0 && (mundo->verificaCelulaMar(this->x - 1, this->y) == CELULA_MAR)) {

		VerificaPorto = mundo->verificaCelulaPorto(this->x - 1, this->y);

		if (VerificaPorto == CELULA_PORTO_AMIGO) {

			this->x = this->x - 1;

			return MOVE_VALIDO;
		}

		if (VerificaPorto == CELULA_SEM_PORTO) {

			if (mundo->verificaCelulaNavio(this->x - 1, this->y) != CELULA_NAVIO) {

				this->x = this->x - 1;

				return MOVE_VALIDO;
			}
			else {

				return MOVE_INVALIDO;

			}
		}
		if (VerificaPorto == CELULA_PORTO_INIMIGO) {
			this->x = this->x - 1;
			return MOVE_VALIDO;
		}
	}
	else {

		// Aqui vai verificar se vai existir peixe na celula 
		Superficie *auxMar = mundo->VerificaExistenciaPeixe(mundo->getDimX() - 1, this->y);
		
		if (this->estado == autoMove || this->estado == normal) {
			
			if (auxMar != nullptr &&  this->QuantMercadoria + 1 <= ESCUNA_QUANT_MAX_CARGA) {

				this->QuantPeixe = this->QuantPeixe + PEIXE_PESCADO;

				this->QuantMercadoria = this->QuantMercadoria + PEIXE_PESCADO;

				auxMar->PescaCardumeMar(turnoJogo);
				cout << "Turno em que o peixe foi pescado " << auxMar->getTurno() << endl;

			}
		}

		if (x == 0 && (mundo->verificaCelulaMar(mundo->getDimX() - 1, this->y) == CELULA_MAR))

			VerificaPorto = mundo->verificaCelulaPorto(mundo->getDimX() - 1, this->y);

		if (VerificaPorto == CELULA_PORTO_AMIGO) {

			this->x = mundo->getDimX() - 1;

			return MOVE_VALIDO;
		}
		if (VerificaPorto == CELULA_SEM_PORTO) {

			if (mundo->verificaCelulaNavio(mundo->getDimX() - 1, this->y) != CELULA_NAVIO) {

				this->x = mundo->getDimX() - 1;

				return MOVE_VALIDO;
			}
			else {

				return MOVE_INVALIDO;

			}
		}
		if (VerificaPorto == CELULA_PORTO_INIMIGO) {
			this->x = mundo->getDimX() - 1;
			return MOVE_VALIDO;
		}
	}
	return MOVE_INVALIDO;
}
int Escuna::FmoveDireita(int turnoJogo) {

			// Aqui vai verificar se vai existir peixe na celula 
		Superficie *auxMar = mundo->VerificaExistenciaPeixe(this->x + 1, this->y);
		
		if (this->estado == autoMove || this->estado == normal) {
			
			if (auxMar != nullptr && this->QuantMercadoria + 1 <= ESCUNA_QUANT_MAX_CARGA) {

				this->QuantPeixe = this->QuantPeixe + PEIXE_PESCADO;

				this->QuantMercadoria = this->QuantMercadoria + PEIXE_PESCADO;

				auxMar->PescaCardumeMar(turnoJogo);

				cout << "Turno em que o peixe foi pescado " << auxMar->getTurno() << endl;

			}
		}
	int VerificaPorto = 0;
	//e ver se a nova pos est� dentro de agua!
	if (x < mundo->getDimX() - 1 && (mundo->verificaCelulaMar(this->x + 1, this->y) == CELULA_MAR)) {



		VerificaPorto = mundo->verificaCelulaPorto(this->x + 1, this->y);

		if (VerificaPorto == CELULA_PORTO_AMIGO) {

			this->x = this->x + 1;

			return MOVE_VALIDO;
		}
		if (VerificaPorto == CELULA_SEM_PORTO) {

			if (mundo->verificaCelulaNavio(this->x + 1, this->y) != CELULA_NAVIO) {

				this->x = this->x + 1;

				return MOVE_VALIDO;
			}
			else {

				return MOVE_INVALIDO;

			}
		}
		if (VerificaPorto == CELULA_PORTO_INIMIGO) {
			this->x = this->x + 1;
			return MOVE_VALIDO;
		}
	}
	else {
		// Aqui vai verificar se vai existir peixe na celula 
		Superficie *auxMar = mundo->VerificaExistenciaPeixe(0, this->y);
		
		if (this->estado == autoMove || this->estado == normal) {
			
			if (auxMar != nullptr && this->QuantMercadoria + 1 <= ESCUNA_QUANT_MAX_CARGA) {

				this->QuantPeixe = this->QuantPeixe + PEIXE_PESCADO;

				this->QuantMercadoria = this->QuantMercadoria + PEIXE_PESCADO;

				auxMar->PescaCardumeMar(turnoJogo);

				cout << "Turno em que o peixe foi pescado " << auxMar->getTurno() << endl;

			}
		}
		if (x == mundo->getDimX() - 1 && (mundo->verificaCelulaMar(0, this->y) == CELULA_MAR)) {

			VerificaPorto = mundo->verificaCelulaPorto(0, this->y);

			if (VerificaPorto == CELULA_PORTO_AMIGO) {

				this->x = 0;

				return MOVE_VALIDO;
			}

			if (VerificaPorto == CELULA_SEM_PORTO) {

				if (mundo->verificaCelulaNavio(0, this->y) != CELULA_NAVIO) {

					this->x = 0;

					return MOVE_VALIDO;
				}
				else {

					return MOVE_INVALIDO;

				}
			}

			if (VerificaPorto == CELULA_PORTO_INIMIGO) {
				this->x = 0;
				return MOVE_VALIDO;
			}
		}
		
	}
	return MOVE_INVALIDO;
}
int Escuna::FmoveCima(int turnoJogo) {

	// Aqui vai verificar se vai existir peixe na celula 
	Superficie *auxMar = mundo->VerificaExistenciaPeixe(this->x, this->y - 1);
	
	if (this->estado == autoMove || this->estado == normal) {
		
		if (auxMar != nullptr && this->QuantMercadoria + 1 <= ESCUNA_QUANT_MAX_CARGA) {

			this->QuantPeixe = this->QuantPeixe + PEIXE_PESCADO;

			this->QuantMercadoria = this->QuantMercadoria + PEIXE_PESCADO;

			auxMar->PescaCardumeMar(turnoJogo);

			cout << "Turno em que o peixe foi pescado " << auxMar->getTurno() << endl;

		}
	}
	int VerificaPorto = 0;
	//e ver se a nova pos est� dentro de agua!
	if (y > 0 && (mundo->verificaCelulaMar(this->x, this->y - 1) == CELULA_MAR)) {

		VerificaPorto = mundo->verificaCelulaPorto(this->x, this->y - 1);

		if (VerificaPorto == CELULA_PORTO_AMIGO) {

			this->y = this->y - 1;

			return MOVE_VALIDO;
		}

		if (VerificaPorto == CELULA_SEM_PORTO) {

			if (mundo->verificaCelulaNavio(this->x, this->y - 1) != CELULA_NAVIO) {

				this->y = this->y - 1;

				return MOVE_VALIDO;
			}
			else {

				return MOVE_INVALIDO;

			}
		}

		if (VerificaPorto == CELULA_PORTO_INIMIGO) {
			this->y = this->y - 1;
			return MOVE_VALIDO;
		}

	}
	else {

		// Aqui vai verificar se vai existir peixe na celula 
		Superficie *auxMar = mundo->VerificaExistenciaPeixe(this->x, mundo->getDimY() - 1);
		
		if (this->estado == autoMove || this->estado == normal) {
			
			if (auxMar != nullptr && this->QuantMercadoria + 1 <= ESCUNA_QUANT_MAX_CARGA) {

				this->QuantPeixe = this->QuantPeixe + PEIXE_PESCADO;

				this->QuantMercadoria = this->QuantMercadoria + PEIXE_PESCADO;

				auxMar->PescaCardumeMar(turnoJogo);

				cout << "Turno em que o peixe foi pescado " << auxMar->getTurno() << endl;


			}
		}

		if (y == 0 && (mundo->verificaCelulaMar(this->x, mundo->getDimY() - 1) == CELULA_MAR)) {

			VerificaPorto = mundo->verificaCelulaPorto(this->x, mundo->getDimY() - 1);

			if (VerificaPorto == CELULA_PORTO_AMIGO) {

				this->y = mundo->getDimY() - 1;

				return MOVE_VALIDO;
			}

			if (VerificaPorto == CELULA_SEM_PORTO) {

				if (mundo->verificaCelulaNavio(this->x, mundo->getDimY() - 1) != CELULA_NAVIO) {

					this->y = mundo->getDimY() - 1;

					return MOVE_VALIDO;

				}
				else {

					return MOVE_INVALIDO;
				}
			}
			if (VerificaPorto == CELULA_PORTO_INIMIGO) {
				this->y = mundo->getDimY() - 1;
				return MOVE_VALIDO;
			}
		}
		
	}

	return MOVE_INVALIDO;
}
int Escuna::FmoveBaixo(int turnoJogo) {

	// Aqui vai verificar se vai existir peixe na celula 
	Superficie *auxMar = mundo->VerificaExistenciaPeixe(this->x, this->y + 1);
	if (this->estado == autoMove || this->estado == normal) {
		
		if (auxMar != nullptr && this->QuantMercadoria + 1 <= ESCUNA_QUANT_MAX_CARGA) {

			this->QuantPeixe = this->QuantPeixe + PEIXE_PESCADO;

			this->QuantMercadoria = this->QuantMercadoria + PEIXE_PESCADO;

			auxMar->PescaCardumeMar(turnoJogo);

			cout << "Turno em que o peixe foi pescado " << auxMar->getTurno() << endl;

		}
	}
	int VerificaPorto = 0;
	//e ver se a nova pos est� dentro de agua!
	if (y < mundo->getDimY() - 1 && (mundo->verificaCelulaMar(this->x, this->y + 1) == CELULA_MAR)) {

		VerificaPorto = mundo->verificaCelulaPorto(this->x, this->y + 1);

		if (VerificaPorto == CELULA_PORTO_AMIGO) {

			this->y = this->y + 1;

			return MOVE_VALIDO;
		}

		if (VerificaPorto == CELULA_SEM_PORTO) {

			if (mundo->verificaCelulaNavio(this->x, this->y + 1) != CELULA_NAVIO) {

				this->y = this->y + 1;

				return MOVE_VALIDO;
			}
			else {

				return MOVE_INVALIDO;
			}
		}
		if (VerificaPorto == CELULA_PORTO_INIMIGO) {
			this->y = this->y + 1;
			return MOVE_VALIDO;
		}
		
	}
	else {

		// Aqui vai verificar se vai existir peixe na celula 
		Superficie *auxMar = mundo->VerificaExistenciaPeixe(this->x, 0);
		if (this->estado == autoMove || this->estado == normal) {
		
			if (auxMar != nullptr && this->QuantMercadoria + 1 <= ESCUNA_QUANT_MAX_CARGA) {

				this->QuantPeixe = this->QuantPeixe + PEIXE_PESCADO;

				this->QuantMercadoria = this->QuantMercadoria + PEIXE_PESCADO;

				auxMar->PescaCardumeMar(turnoJogo);

				cout << "Turno em que o peixe foi pescado " << auxMar->getTurno() << endl;

			}
		}

		if (y == mundo->getDimY() - 1 && (mundo->verificaCelulaMar(this->x, 0) == CELULA_MAR)) {

			VerificaPorto = mundo->verificaCelulaPorto(this->x, 0);

			if (VerificaPorto == CELULA_PORTO_AMIGO) {

				this->y = 0;

				return MOVE_VALIDO;
			}

			if (VerificaPorto == CELULA_SEM_PORTO) {

				if (mundo->verificaCelulaNavio(this->x, 0) != CELULA_NAVIO) {

					this->y = 0;

					return MOVE_VALIDO;
				}
				else {

					return MOVE_INVALIDO;
				}
			}
			if (VerificaPorto == CELULA_PORTO_INIMIGO) {
				this->y = 0;
				return MOVE_VALIDO;
			}
		}
		
	}
	return MOVE_INVALIDO;
}
int Escuna::FmoveCimaEsquerda(int turnoJogo) {

	
	int VerificaPorto = 0;
	//anda normal
	if ((y > 0 && y <= mundo->getDimY() - 1) && (x > 0 && x <= mundo->getDimX() - 1) && (mundo->verificaCelulaMar(this->x - 1, this->y - 1) == CELULA_MAR)) {

		// Aqui vai verificar se vai existir peixe na celula 
		Superficie *auxMar = mundo->VerificaExistenciaPeixe(this->x - 1, this->y - 1);

		if ( this->estado == autoMove || this->estado == normal) {

			if (auxMar != nullptr && this->QuantMercadoria + 1 <= ESCUNA_QUANT_MAX_CARGA) {

				this->QuantPeixe = this->QuantPeixe + PEIXE_PESCADO;

				this->QuantMercadoria = this->QuantMercadoria + PEIXE_PESCADO;

				auxMar->PescaCardumeMar(turnoJogo);

				cout << "Turno em que o peixe foi pescado " << auxMar->getTurno() << endl;

			}
		}


		VerificaPorto = mundo->verificaCelulaPorto(this->x - 1, this->y - 1);

		if (VerificaPorto == CELULA_PORTO_AMIGO) {

			this->y = this->y - 1;

			this->x = this->x - 1;

			return MOVE_VALIDO;
		}

		if (VerificaPorto == CELULA_SEM_PORTO) {

			if (mundo->verificaCelulaNavio(this->x - 1, this->y - 1) != CELULA_NAVIO) {

				this->y = this->y - 1;

				this->x = this->x - 1;

				return MOVE_VALIDO;
			}
			else {

				return MOVE_INVALIDO;
			}
		}

		if (VerificaPorto == CELULA_PORTO_INIMIGO) {
			this->y = this->y - 1;
			this->x = this->x - 1;
			return MOVE_VALIDO;
		}
	}

	if ((y == 0 && (x > 0 && x <= mundo->getDimX() - 1)) && (mundo->verificaCelulaMar(this->x - 1, mundo->getDimY() - 1) == CELULA_MAR)) {

		////encostado a cima
		Superficie *auxMar = mundo->VerificaExistenciaPeixe(this->x - 1, mundo->getDimY() - 1);

		if (this->estado == autoMove || this->estado == normal) {

			if (auxMar != nullptr &&  this->QuantMercadoria + 1 <= ESCUNA_QUANT_MAX_CARGA) {

				this->QuantPeixe = this->QuantPeixe + PEIXE_PESCADO;

				this->QuantMercadoria = this->QuantMercadoria + PEIXE_PESCADO;

				auxMar->PescaCardumeMar(turnoJogo);

				cout << "Turno em que o peixe foi pescado " << auxMar->getTurno() << endl;

			}
		}

		VerificaPorto = mundo->verificaCelulaPorto(this->x - 1, mundo->getDimY() - 1);

		if (VerificaPorto == CELULA_PORTO_AMIGO) {

			this->x = this->x - 1;

			this->y = mundo->getDimY() - 1;

			return MOVE_VALIDO;
		}

		if (VerificaPorto == CELULA_SEM_PORTO) {

			if (mundo->verificaCelulaNavio(this->x - 1, mundo->getDimY() - 1) != CELULA_NAVIO) {

				this->x = this->x - 1;

				this->y = mundo->getDimY() - 1;

				return MOVE_VALIDO;
			}
			else {

				return MOVE_INVALIDO;
			}
		}

		if (VerificaPorto == CELULA_PORTO_INIMIGO) {
			this->x = this->x - 1;
			this->y = mundo->getDimY() - 1;
			return MOVE_VALIDO;
		}

		
	}
	////encostado � esquerda
	if ((x == 0 && (y > 0 && y <= mundo->getDimY() - 1)) && (mundo->verificaCelulaMar(mundo->getDimX() - 1, this->y - 1) == CELULA_MAR)) {

		// verifica peixe
		Superficie *auxMar = mundo->VerificaExistenciaPeixe(mundo->getDimX() - 1, this->y - 1);

		if (this->estado == autoMove || this->estado == normal) {

			if (auxMar != nullptr &&  this->QuantMercadoria + 1 <= ESCUNA_QUANT_MAX_CARGA) {

				this->QuantPeixe = this->QuantPeixe + PEIXE_PESCADO;

				this->QuantMercadoria = this->QuantMercadoria + PEIXE_PESCADO;

				auxMar->PescaCardumeMar(turnoJogo);

			}
		}

		VerificaPorto = mundo->verificaCelulaPorto(mundo->getDimX() - 1, this->y - 1);

		if (VerificaPorto == CELULA_PORTO_AMIGO) {

			this->x = mundo->getDimX() - 1;

			this->y = this->y - 1;

			return MOVE_VALIDO;
		}

		if (VerificaPorto == CELULA_SEM_PORTO) {

			if (mundo->verificaCelulaNavio(mundo->getDimX() - 1, this->y - 1) != CELULA_NAVIO) {

				this->x = mundo->getDimX() - 1;

				this->y = this->y - 1;

				return MOVE_VALIDO;
			}
			else {

				return MOVE_INVALIDO;
			}
		}

		if (VerificaPorto == CELULA_PORTO_INIMIGO) {
			this->x = mundo->getDimX() - 1;
			this->y = this->y - 1;
			return MOVE_VALIDO;
		}
		
	}
	//canto superior esquerdo
	if ((y == 0 && x == 0) && (mundo->verificaCelulaMar(mundo->getDimX() - 1, mundo->getDimY() - 1) == CELULA_MAR)) {

		// verifica peixe
		Superficie *auxMar = mundo->VerificaExistenciaPeixe(mundo->getDimX() - 1, mundo->getDimY() - 1);

		if (this->estado == autoMove || this->estado == normal) {

			if (auxMar != nullptr &&  this->QuantMercadoria + 1 <= ESCUNA_QUANT_MAX_CARGA) {

				this->QuantPeixe = this->QuantPeixe + PEIXE_PESCADO;

				this->QuantMercadoria = this->QuantMercadoria + PEIXE_PESCADO;

				auxMar->PescaCardumeMar(turnoJogo);

			}
		}

		VerificaPorto = mundo->verificaCelulaPorto(mundo->getDimX() - 1, mundo->getDimY() - 1);

		if (VerificaPorto == CELULA_PORTO_AMIGO) {

			this->x = mundo->getDimX() - 1;

			this->y = mundo->getDimY() - 1;

			return MOVE_VALIDO;
		}

		if (VerificaPorto == CELULA_SEM_PORTO) {

			if (mundo->verificaCelulaNavio(mundo->getDimX() - 1, mundo->getDimY() - 1) != CELULA_NAVIO) {

				this->x = mundo->getDimX() - 1;

				this->y = mundo->getDimY() - 1;

				return MOVE_VALIDO;
			}
			else {

				return MOVE_INVALIDO;
			}
		}

		if (VerificaPorto == CELULA_PORTO_INIMIGO) {
			this->x = mundo->getDimX() - 1;
			this->y = mundo->getDimY() - 1;
			return MOVE_VALIDO;
		}
		
	}
	return MOVE_INVALIDO;
}
int Escuna::FmoveCimaDireita(int turnoJogo) {
	int VerificaPorto = 0;
	//anda normal
	if (y > 0 && y <= mundo->getDimY() - 1 && x > 0 && x < mundo->getDimX() - 1 && (mundo->verificaCelulaMar(this->x + 1, this->y - 1) == CELULA_MAR)) {

		// verifica peixe
		Superficie *auxMar = mundo->VerificaExistenciaPeixe(this->x + 1, this->y - 1);

		if ( this->estado == autoMove || this->estado == normal) {

			if (auxMar != nullptr && this->QuantMercadoria + 1 <= ESCUNA_QUANT_MAX_CARGA) {

				this->QuantPeixe = this->QuantPeixe + PEIXE_PESCADO;

				this->QuantMercadoria = this->QuantMercadoria + PEIXE_PESCADO;

				auxMar->PescaCardumeMar(turnoJogo);

			}
		}

		VerificaPorto = mundo->verificaCelulaPorto(this->x + 1, this->y - 1);

		if (VerificaPorto == CELULA_PORTO_AMIGO) {

			this->y = this->y - 1;

			this->x = this->x + 1;

			return MOVE_VALIDO;
		}

		if (VerificaPorto == CELULA_SEM_PORTO) {

			if (mundo->verificaCelulaNavio(this->x + 1, this->y - 1) != CELULA_NAVIO) {

				this->y = this->y - 1;

				this->x = this->x + 1;

				return MOVE_VALIDO;
			}
			else {

				return MOVE_INVALIDO;
			}
		}

		if (VerificaPorto == CELULA_PORTO_INIMIGO) {
			this->y = this->y - 1;
			this->x = this->x + 1;
			return MOVE_VALIDO;
		}
	}
	//encostado a cima
	if ((y == 0 && (x >= 0 && x < mundo->getDimX() - 1)) && (mundo->verificaCelulaMar(this->x + 1, mundo->getDimY() - 1) == CELULA_MAR)) {

		// verifica peixe
		Superficie *auxMar = mundo->VerificaExistenciaPeixe(this->x + 1, mundo->getDimY() - 1);

		if (this->estado == autoMove || this->estado == normal) {

			if (auxMar != nullptr && this->QuantMercadoria + 1 <= ESCUNA_QUANT_MAX_CARGA) {

				this->QuantPeixe = this->QuantPeixe + PEIXE_PESCADO;

				this->QuantMercadoria = this->QuantMercadoria + PEIXE_PESCADO;

				auxMar->PescaCardumeMar(turnoJogo);

			}
		}

		VerificaPorto = mundo->verificaCelulaPorto(this->x + 1, mundo->getDimY() - 1);

		if (VerificaPorto == CELULA_PORTO_AMIGO) {

			this->x = this->x + 1;

			this->y = mundo->getDimY() - 1;

			return MOVE_VALIDO;
		}

		if (VerificaPorto == CELULA_SEM_PORTO) {

			if (mundo->verificaCelulaNavio(this->x + 1, mundo->getDimY() - 1) != CELULA_NAVIO) {

				this->x = this->x + 1;

				this->y = mundo->getDimY() - 1;

				return MOVE_VALIDO;
			}
			else {

				return MOVE_INVALIDO;
			}
		}

		if (VerificaPorto == CELULA_PORTO_INIMIGO) {
			this->x = this->x + 1;
			this->y = mundo->getDimY() - 1;
			return MOVE_VALIDO;
		}
		
	}
	//encostado � direita
	if ((x == mundo->getDimX() - 1 && y > 0 && y <= mundo->getDimY() - 1) && (mundo->verificaCelulaMar(0, this->y - 1) == CELULA_MAR)) {

		// verifica peixe
		Superficie *auxMar = mundo->VerificaExistenciaPeixe(0, this->y - 1);

		if (this->estado == autoMove || this->estado == normal) {

			if (auxMar != nullptr &&  this->QuantMercadoria + 1 <= ESCUNA_QUANT_MAX_CARGA) {

				this->QuantPeixe = this->QuantPeixe + PEIXE_PESCADO;

				this->QuantMercadoria = this->QuantMercadoria + PEIXE_PESCADO;

				auxMar->PescaCardumeMar(turnoJogo);
			}
		}

		VerificaPorto = mundo->verificaCelulaPorto(0, this->y - 1);

		if (VerificaPorto == CELULA_PORTO_AMIGO) {

			this->x = 0;

			this->y = this->y - 1;

			return MOVE_VALIDO;
		}

		if (VerificaPorto == CELULA_SEM_PORTO) {

			if (mundo->verificaCelulaNavio(0, this->y - 1) != CELULA_NAVIO) {

				this->x = 0;

				this->y = this->y - 1;

				return MOVE_VALIDO;
			}
			else {

				return MOVE_INVALIDO;
			}
		}

		if (VerificaPorto == CELULA_PORTO_INIMIGO) {
			this->x = 0;
			this->y = this->y - 1;
			return MOVE_VALIDO;
		}
		
	}
	//canto superior direito
	if (y == 0 && x == mundo->getDimX() - 1 && (mundo->verificaCelulaMar(0, mundo->getDimY() - 1) == CELULA_MAR)) {

		// verifica peixe
		Superficie *auxMar = mundo->VerificaExistenciaPeixe(0, mundo->getDimY() - 1);

		if (this->estado == autoMove || this->estado == normal) {

			if (auxMar != nullptr &&  this->QuantMercadoria + 1 <= ESCUNA_QUANT_MAX_CARGA) {

				this->QuantPeixe = this->QuantPeixe + PEIXE_PESCADO;

				this->QuantMercadoria = this->QuantMercadoria + PEIXE_PESCADO;

				auxMar->PescaCardumeMar(turnoJogo);

			}
		}

		VerificaPorto = mundo->verificaCelulaPorto(0, mundo->getDimY() - 1);

		if (VerificaPorto == CELULA_PORTO_AMIGO) {

			this->x = 0;

			this->y = mundo->getDimY() - 1;

			return MOVE_VALIDO;
		}

		if (VerificaPorto == CELULA_SEM_PORTO) {

			if (mundo->verificaCelulaNavio(0, mundo->getDimY() - 1) != CELULA_NAVIO) {

				this->x = 0;

				this->y = mundo->getDimY() - 1;

				return MOVE_VALIDO;
			}
			else {

				return MOVE_INVALIDO;
			}
		}

		if (VerificaPorto == CELULA_PORTO_INIMIGO) {
			this->x = 0;
			this->y = mundo->getDimY() - 1;
			return MOVE_VALIDO;
		}
		
	}
	return MOVE_INVALIDO;
}
int Escuna::FmoveBaixoEsquerda(int turnoJogo) {
	int VerificaPorto = 0;
	//anda normal
	if ((y >= 0 && y < mundo->getDimY() - 1) && (x > 0 && x <= mundo->getDimX() - 1) && (mundo->verificaCelulaMar(this->x - 1, this->y + 1) == CELULA_MAR)) {

		Superficie *auxMar = mundo->VerificaExistenciaPeixe(this->x - 1, this->y + 1);

		if (this->estado == autoMove || this->estado == normal) {

			if (auxMar != nullptr &&  this->QuantMercadoria + 1 <= ESCUNA_QUANT_MAX_CARGA) {

				this->QuantPeixe = this->QuantPeixe + PEIXE_PESCADO;

				this->QuantMercadoria = this->QuantMercadoria + PEIXE_PESCADO;

				auxMar->PescaCardumeMar(turnoJogo);

			}
		}

		VerificaPorto = mundo->verificaCelulaPorto(this->x - 1, this->y + 1);

		if (VerificaPorto == CELULA_PORTO_AMIGO) {

			this->y = this->y + 1;

			this->x = this->x - 1;

			return MOVE_VALIDO;
		}

		if (VerificaPorto == CELULA_SEM_PORTO) {

			if (mundo->verificaCelulaNavio(this->x - 1, this->y + 1) != CELULA_NAVIO) {

				this->y = this->y + 1;

				this->x = this->x - 1;

				return MOVE_VALIDO;
			}
			else {

				return MOVE_INVALIDO;
			}
		}

		if (VerificaPorto == CELULA_PORTO_INIMIGO) {
			this->y = this->y + 1;
			this->x = this->x - 1;
			return MOVE_VALIDO;
		}
		// verifica peixe
	
	}
	//////encostado a baixo
	if ((y == mundo->getDimY() - 1) && (x > 0 && x <= mundo->getDimX() - 1) && (mundo->verificaCelulaMar(this->x - 1, 0) == CELULA_MAR)) {

		// verifica peixe
		Superficie *auxMar = mundo->VerificaExistenciaPeixe(this->x - 1, 0);

		if (this->estado == autoMove || this->estado == normal) {

			if (auxMar != nullptr && this->QuantMercadoria + 1 <= ESCUNA_QUANT_MAX_CARGA) {

				this->QuantPeixe = this->QuantPeixe + PEIXE_PESCADO;

				this->QuantMercadoria = this->QuantMercadoria + PEIXE_PESCADO;

				auxMar->PescaCardumeMar(turnoJogo);

			}
		}

		VerificaPorto = mundo->verificaCelulaPorto(this->x - 1, 0);

		if (VerificaPorto == CELULA_PORTO_AMIGO) {

			this->x = this->x - 1;

			this->y = 0;

			return MOVE_VALIDO;
		}

		if (VerificaPorto == CELULA_SEM_PORTO) {

			if (mundo->verificaCelulaNavio(this->x - 1, 0) != CELULA_NAVIO) {

				this->x = this->x - 1;

				this->y = 0;

				return MOVE_VALIDO;
			}
			else {

				return MOVE_INVALIDO;
			}
		}

		if (VerificaPorto == CELULA_PORTO_INIMIGO) {
			this->x = this->x - 1;
			this->y = 0;
			return MOVE_VALIDO;
		}
		

	}
	//////encostado � esquerda
	if ((x == 0) && (y >= 0 && y < mundo->getDimY() - 1) && (mundo->verificaCelulaMar(mundo->getDimX() - 1, this->y + 1) == CELULA_MAR)) {

		// verifica peixe
		Superficie *auxMar = mundo->VerificaExistenciaPeixe(mundo->getDimX() - 1, this->y + 1);

		if (this->estado == autoMove || this->estado == normal) {

			if (auxMar != nullptr &&  this->QuantMercadoria + 1 <= ESCUNA_QUANT_MAX_CARGA) {

				this->QuantPeixe = this->QuantPeixe + PEIXE_PESCADO;

				this->QuantMercadoria = this->QuantMercadoria + PEIXE_PESCADO;

				auxMar->PescaCardumeMar(turnoJogo);

			}
		}

		VerificaPorto = mundo->verificaCelulaPorto(mundo->getDimX() - 1, this->y + 1);

		if (VerificaPorto == CELULA_PORTO_AMIGO) {

			this->x = mundo->getDimX() - 1;
			this->y = this->y + 1;
			return MOVE_VALIDO;
		}

		if (VerificaPorto == CELULA_SEM_PORTO) {

			if (mundo->verificaCelulaNavio(mundo->getDimX() - 1, this->y + 1) != CELULA_NAVIO) {

				this->x = mundo->getDimX() - 1;

				this->y = this->y + 1;

				return MOVE_VALIDO;
			}
			else {

				return MOVE_INVALIDO;
			}
		}

		if (VerificaPorto == CELULA_PORTO_INIMIGO) {
			this->x = mundo->getDimX() - 1;
			this->y = this->y + 1;
			return MOVE_VALIDO;
		}
		
	}
	//canto inferior esquerdo
	if ((y == mundo->getDimY() - 1 && x == 0) && (mundo->verificaCelulaMar(mundo->getDimX() - 1, 0) == CELULA_MAR)) {

		// verifica peixe
		Superficie *auxMar = mundo->VerificaExistenciaPeixe(mundo->getDimX() - 1, 0);

		if (this->estado == autoMove || this->estado == normal) {

			if (auxMar != nullptr && this->QuantMercadoria + 1 <= ESCUNA_QUANT_MAX_CARGA) {

				this->QuantPeixe = this->QuantPeixe + PEIXE_PESCADO;

				this->QuantMercadoria = this->QuantMercadoria + PEIXE_PESCADO;

				auxMar->PescaCardumeMar(turnoJogo);

			}
		}

		VerificaPorto = mundo->verificaCelulaPorto(mundo->getDimX() - 1, 0);

		if (VerificaPorto == CELULA_PORTO_AMIGO) {

			this->x = mundo->getDimX() - 1;

			this->y = 0;

			return MOVE_VALIDO;
		}

		if (VerificaPorto == CELULA_SEM_PORTO) {

			if (mundo->verificaCelulaNavio(mundo->getDimX() - 1, 0) != CELULA_NAVIO) {

				this->x = mundo->getDimX() - 1;

				this->y = 0;

				return MOVE_VALIDO;
			}
			else {

				return MOVE_INVALIDO;
			}
		}

		if (VerificaPorto == CELULA_PORTO_INIMIGO) {
			this->x = mundo->getDimX() - 1;
			this->y = 0;
			return MOVE_VALIDO;
		}
		
	}
	return MOVE_INVALIDO;
}
int Escuna::FmoveBaixoDireita(int turnoJogo) {
	int VerificaPorto = 0;
	//anda normal
	if ((y >= 0 && y < mundo->getDimY() - 1) && (x >= 0 && x < mundo->getDimX() - 1) && (mundo->verificaCelulaMar(this->x + 1, this->y + 1) == CELULA_MAR)) {

		// verifica peixe
		Superficie *auxMar = mundo->VerificaExistenciaPeixe(this->x + 1, this->y + 1);

		if (this->estado == autoMove || this->estado == normal) {

			if (auxMar != nullptr && this->QuantMercadoria + 1 <= ESCUNA_QUANT_MAX_CARGA) {

				this->QuantPeixe = this->QuantPeixe + PEIXE_PESCADO;

				this->QuantMercadoria = this->QuantMercadoria + PEIXE_PESCADO;

				auxMar->PescaCardumeMar(turnoJogo);

			}
		}

		VerificaPorto = mundo->verificaCelulaPorto(this->x + 1, this->y + 1);

		if (VerificaPorto == CELULA_PORTO_AMIGO) {

			this->y = this->y + 1;

			this->x = this->x + 1;

			return MOVE_VALIDO;
		}

		if (VerificaPorto == CELULA_SEM_PORTO) {

			if (mundo->verificaCelulaNavio(this->x + 1, this->y + 1) != CELULA_NAVIO) {

				this->y = this->y + 1;

				this->x = this->x + 1;

				return MOVE_VALIDO;
			}
			else {
				return MOVE_INVALIDO;
			}
		}

		if (VerificaPorto == CELULA_PORTO_INIMIGO) {
			this->y = this->y + 1;
			this->x = this->x + 1;
			return MOVE_VALIDO;
		}
		
	}
	////////encostado a baixo
	if ((y == mundo->getDimY() - 1) && (x >= 0 && x < mundo->getDimX() - 1) && (mundo->verificaCelulaMar(this->x + 1, 0) == CELULA_MAR)) {

		// verifica peixe
		Superficie *auxMar = mundo->VerificaExistenciaPeixe(this->x + 1, 0);

		if (this->estado == autoMove || this->estado == normal) {

			if (auxMar != nullptr && this->QuantMercadoria + 1 <= ESCUNA_QUANT_MAX_CARGA) {

				this->QuantPeixe = this->QuantPeixe + PEIXE_PESCADO;

				this->QuantMercadoria = this->QuantMercadoria + PEIXE_PESCADO;

				auxMar->PescaCardumeMar(turnoJogo);

			}
		}

		VerificaPorto = mundo->verificaCelulaPorto(this->x + 1, 0);

		if (VerificaPorto == CELULA_PORTO_AMIGO) {

			this->x = this->x + 1;

			this->y = 0;

			return MOVE_VALIDO;
		}

		if (VerificaPorto == CELULA_SEM_PORTO) {

			if (mundo->verificaCelulaNavio(this->x + 1, 0) != CELULA_NAVIO) {

				this->x = this->x + 1;

				this->y = 0;

				return MOVE_VALIDO;
			}
			else {

				return MOVE_INVALIDO;
			}
		}

		if (VerificaPorto == CELULA_PORTO_INIMIGO) {
			this->x = this->x + 1;
			this->y = 0;
			return MOVE_VALIDO;
		}
		
	}
	////////encostado � direita
	if ((x == mundo->getDimX() - 1) && (y >= 0 && y < mundo->getDimY() - 1) && (mundo->verificaCelulaMar(0, this->y + 1) == CELULA_MAR)) {

		// verifica peixe
		Superficie *auxMar = mundo->VerificaExistenciaPeixe(0, this->y + 1);

		if (this->estado == autoMove || this->estado == normal) {

			if (auxMar != nullptr && this->QuantMercadoria + 1 <= ESCUNA_QUANT_MAX_CARGA) {

				this->QuantPeixe = this->QuantPeixe + PEIXE_PESCADO;

				this->QuantMercadoria = this->QuantMercadoria + PEIXE_PESCADO;

				auxMar->PescaCardumeMar(turnoJogo);

			}
		}

		VerificaPorto = mundo->verificaCelulaPorto(0, this->y + 1);

		if (VerificaPorto == CELULA_PORTO_AMIGO) {

			this->x = 0;

			this->y = this->y + 1;

			return MOVE_VALIDO;
		}

		if (VerificaPorto == CELULA_SEM_PORTO) {

			if (mundo->verificaCelulaNavio(0, this->y + 1) != CELULA_NAVIO) {

				this->x = 0;

				this->y = this->y + 1;

				return MOVE_VALIDO;
			}
			else {

				return MOVE_INVALIDO;
			}
		}

		if (VerificaPorto == CELULA_PORTO_INIMIGO) {
			this->x = 0;
			this->y = this->y + 1;
			return MOVE_VALIDO;
		}
		
	}
	////canto inferior esquerdo
	if ((y == mundo->getDimY() - 1 && x == mundo->getDimX() - 1) && (mundo->verificaCelulaMar(0, 0) == CELULA_MAR)) {

		// verifica peixe
		Superficie *auxMar = mundo->VerificaExistenciaPeixe(0, 0);

		if (this->estado == autoMove || this->estado == normal) {

			if (auxMar != nullptr && this->QuantMercadoria + 1 <= ESCUNA_QUANT_MAX_CARGA) {

				this->QuantPeixe = this->QuantPeixe + PEIXE_PESCADO;

				this->QuantMercadoria = this->QuantMercadoria + PEIXE_PESCADO;

				auxMar->PescaCardumeMar(turnoJogo);

			}
		}

		VerificaPorto = mundo->verificaCelulaPorto(0, 0);

		if (VerificaPorto == CELULA_PORTO_AMIGO) {

			this->x = 0;

			this->y = 0;

			return MOVE_VALIDO;
		}

		if (VerificaPorto == CELULA_SEM_PORTO) {

			if (mundo->verificaCelulaNavio(0, this->y + 1) != CELULA_NAVIO) {

				this->x = 0;

				this->y = 0;

				return MOVE_VALIDO;
			}
			else {

				return MOVE_INVALIDO;
			}
		}

		if (VerificaPorto == CELULA_PORTO_INIMIGO) {
			this->x = 0;
			this->y = 0;
			return MOVE_VALIDO;
		}
		
	}
	return MOVE_INVALIDO;
}
int Escuna::moveNavio(int direcao, int turnoJogo) {

	if (this->quantSoldados == 0)
		this->estado = aDeriva;

	if (this->QuantMercadoria == ESCUNA_QUANT_MAX_CARGA){

			Porto *aux=mundo->getPortoAmigo();

			if (aux != nullptr) 
				mundo->setVaiPara(this->getId(), aux->getX(), aux->getY());
		}

	switch (direcao) {

	case moveEsquerda:
		if (FmoveEsquerda(turnoJogo) == MOVE_VALIDO) {
			if (this->estado == normal)
				soldadosBebemAgua();
			return MOVE_VALIDO;
		}
		else
			break;
	case moveDireita:
		if (FmoveDireita(turnoJogo) == MOVE_VALIDO) {
			if (this->estado == normal)
				soldadosBebemAgua();
			return MOVE_VALIDO;
		}
		else
			break;
	case moveCima:
		if (FmoveCima(turnoJogo) == MOVE_VALIDO) {
			if (this->estado == normal)
				soldadosBebemAgua();
			return MOVE_VALIDO;
		}
		else
			break;
	case moveBaixo:
		if (FmoveBaixo(turnoJogo) == MOVE_VALIDO) {
			if (this->estado == normal)
				soldadosBebemAgua();
			return MOVE_VALIDO;
		}
		else
			break;
	case moveCimaEsquerda:
		if (FmoveCimaEsquerda(turnoJogo) == MOVE_VALIDO) {
			if (this->estado == normal)
				soldadosBebemAgua();
			return MOVE_VALIDO;
		}
		else
			break;
	case moveCimaDireita:
		if (FmoveCimaDireita(turnoJogo) == MOVE_VALIDO) {
			if (this->estado == normal)
				soldadosBebemAgua();
			return MOVE_VALIDO;
		}
		else
			break;
	case moveBaixoEsquerda:
		if (FmoveBaixoEsquerda(turnoJogo) == MOVE_VALIDO) {
			if (this->estado == normal)
				soldadosBebemAgua();
			return MOVE_VALIDO;
		}
		else
			break;
	case moveBaixoDireita:
		if (FmoveBaixoDireita(turnoJogo) == MOVE_VALIDO) {
			if (this->estado == normal)
				soldadosBebemAgua();
			return MOVE_VALIDO;
		}
		else
			break;
	}
	return MOVE_INVALIDO;
}
void Escuna::adicionaMercadoriaNavio(int quantCarga)
{
	if (this->QuantMercadoria + quantCarga <= ESCUNA_QUANT_MAX_CARGA)
		this->QuantMercadoria = QuantMercadoria + quantCarga;
	else
		this->QuantMercadoria = ESCUNA_QUANT_MAX_CARGA;
}
void Escuna::setMercadoriaNavio(int Quant)
{
	this->QuantMercadoria = Quant;
}
void Escuna::RetiraMercadoriaNavio(int quantCarga)
{
	if (this->QuantPeixe - (quantCarga / 2) >= 0)
		this->QuantPeixe = this->QuantPeixe - (quantCarga / 2);

	if (this->QuantMercadoria - quantCarga >= 0)
		this->QuantMercadoria = QuantMercadoria - quantCarga;
	else
		this->QuantMercadoria = 0;
}
void Escuna::setQuantidadePeixe(int quantpeixe)
{
	this->QuantPeixe = quantpeixe;
}
void Escuna::AdicionaQuantidadePeixe(int quantpeixe)
{
	if (this->QuantPeixe + quantpeixe <= ESCUNA_QUANT_MAX_CARGA)
		this->QuantPeixe = this->QuantPeixe + quantpeixe;
}
string Escuna::TrataNavioTempestade()
{
	int QuantCargaPerder, probAfundar;

	ostringstream os;

	os << "O navio e do tipo Escuna e vai ser Afetado pela Tempestade" << endl;

	QuantCargaPerder = rand() % 100 + 1;

	probAfundar = rand() % 100 + 1;

	if (probAfundar > PROB_ESCUNA_AFUNDAR_TEMPESTADE && QuantCargaPerder <= PROB_ESCUNA_PERDER_CARGA) {
		RetiraMercadoriaNavio(QuantCargaPerder);
		this->quantSoldados = this->quantSoldados - ((this->quantSoldados * 15) / 100);
		AbasteceAguaNavio();
		os << " O Navio nao afundou ficando com Maxima capacidade de agua .. !" << endl;
	}
	else if (probAfundar <= PROB_ESCUNA_AFUNDAR_TEMPESTADE)
		this->estado = afundado;

	return os.str();
}
Escuna::~Escuna()
{
}
