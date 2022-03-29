/*
 * EDAPark
 *
 * 22.08 EDA
 * TP 2
 * Santiago Michelotti y Albertina Galan
 *
 * Clases y metodos para el control del robot
 * Disclaimer: no tenemos un gamepad asi que no pudimos probar si funciona, pero se incluyeron las funciones
 */
#include "Controller.h"

using namespace std;

/*
 * Metodo que inicializa el robot
 */
Controller::Controller()
{

	cliente = new MQTTClient("controller");

	if (!(cliente->connect("127.0.0.1", 1883, "user", "vdivEMMN3SQWX2Ez")))
	{
		cout << "No se logro establecer conexion" << endl;
	}

	// para utilizar un gamepad/joystick
	if (IsGamepadAvailable(0))
	{
		DrawText("Gamepad Connected: use arrows to move, triggers to turn", 50, 385, 14, WHITE);
		GetGamepadName(0);
	}

	for (int i = 1; i < 5; i++)
	{
		cliente->subscribe("robot1/motor" + to_string(i) + "/voltage");
		cliente->subscribe("robot1/motor" + to_string(i) + "/current");
		cliente->subscribe("robot1/motor" + to_string(i) + "/temperature");
	}

	bool isLEDOn = false;
}

/*
 * Metodo que libera los recursos empleados para controlar el robot
 */
Controller::~Controller()
{
	for (int i = 1; i < 5; i++)
	{
		cliente->unsubscribe("robot1/motor" + to_string(i) + "/voltage");
		cliente->unsubscribe("robot1/motor" + to_string(i) + "/current");
		cliente->unsubscribe("robot1/motor" + to_string(i) + "/temperature");
	}
	cliente->disconnect();
}

/*
 * Metodo que permite transformar un vector de char a un float
 * https://stackoverflow.com/questions/6417438/c-convert-vectorchar-to-double
 * param: vector de char con el payload del mensaje
 * return: la conversion a float del vector
 */
float Controller::getFloatFromArray(std::vector<char> payload)
{

	float convert = 0.0;
	memcpy(&convert, &payload[0], std::min(payload.size(), sizeof(float)));
	return convert;
}

/*
 * Metodo que permite transformar un float a un vector de char, el formato requerido para hacer publish
 * https://stackoverflow.com/questions/6417438/c-convert-vectorchar-to-double
 * param: float para enviar como mensaje
 * return: la conversion a vector char del numero
 */
std::vector<char> Controller::getArrayFromFloat(float payload)
{

	vector<char> data(sizeof(float));
	memcpy(data.data(), &payload, sizeof(float));
	return data;
}

/*
 * Metodo que actualiza el estado del robot e interpreta los comandos de control
 * return: si se pudo realizar la actualizacion 
 */
bool Controller::updateController()
{
	// Impresion de los mensajes en pantalla
	vector<MQTTMessage> mensajes = cliente->getMessages();
	drawTable();
	DrawText("ROBOT1 CONTROL PANEL", 80, 0, 35, RED);

	for (int i = 0; i < mensajes.size(); i++)
	{
		char *msj = const_cast<char *>(mensajes[i].topic.c_str());
		float floatpayload = getFloatFromArray(mensajes[i].payload);
		string stringpayload = to_string(floatpayload);
		char *msjpayload = (char *)(stringpayload.c_str());

		if (mensajes[i].topic.find("1/voltage"))
		{
			if (floatpayload >= 24.0F || floatpayload <= -24.0F)
			{
				DrawText("WARNING", 125 + i * 5000, 125 + i * 5000, 20, WHITE);
			}
			else
			{
				DrawText(msjpayload, 125 + i * 5000, 125 + i * 5000, 20, WHITE);
			}
		}
		if (mensajes[i].topic.find("2/voltage"))
		{
			if (floatpayload >= 24.0F || floatpayload <= -24.0F)
			{
				DrawText("WARNING", 125 + i * 5000, 185 + i * 5000, 20, WHITE);
			}
			else
			{
				DrawText(msjpayload, 125 + i * 5000, 185 + i * 5000, 20, WHITE);
			}
		}
		if (mensajes[i].topic.find("3/voltage"))
		{
			if (floatpayload >= 24.0F || floatpayload <= -24.0F)
			{
				DrawText("WARNING", 125 + i * 5000, 245 + i * 5000, 20, WHITE);
			}
			else
			{
				DrawText(msjpayload, 125 + i * 5000, 245 + i * 5000, 20, WHITE);
			}
		}
		if (mensajes[i].topic.find("4/voltage"))
		{
			if (floatpayload >= 24.0F || floatpayload <= -24.0F)
			{
				DrawText("WARNING", 125 + i * 5000, 305 + i * 5000, 20, WHITE);
			}
			else
			{
				DrawText(msjpayload, 125 + i * 5000, 305 + i * 5000, 20, WHITE);
			}
		}

		if (mensajes[i].topic.find("1/current"))
		{
			if (floatpayload >= 10.0F || floatpayload <= -10.0F)
			{
				DrawText("WARNING", 270 + i * 5000, 125 + i * 5000, 20, WHITE);
			}
			else
			{
				DrawText(msjpayload, 270 + i * 5000, 125 + i * 5000, 20, WHITE);
			}
		}

		if (mensajes[i].topic.find("2/current"))
		{
			if (floatpayload >= 10.0F || floatpayload <= -10.0F)
			{
				DrawText("WARNING", 270 + i * 5000, 185 + i * 5000, 20, WHITE);
			}
			else
			{
				DrawText(msjpayload, 270 + i * 5000, 185 + i * 5000, 20, WHITE);
			}
		}
		if (mensajes[i].topic.find("3/current"))
		{
			if (floatpayload >= 10.0F || floatpayload <= -10.0F)
			{
				DrawText("WARNING", 270 + i * 5000, 245 + i * 5000, 20, WHITE);
			}
			else
			{
				DrawText(msjpayload, 270 + i * 5000, 245 + i * 5000, 20, WHITE);
			}
		}
		if (mensajes[i].topic.find("4/current"))
		{
			if (floatpayload >= 10.0F || floatpayload <= -10.0F)
			{
				DrawText("WARNING", 270 + i * 5000, 305 + i * 5000, 20, WHITE);
			}
			else
			{
				DrawText(msjpayload, 270 + i * 5000, 305 + i * 5000, 20, WHITE);
			}
		}

		if (mensajes[i].topic.find("1/temperature"))
		{
			if (floatpayload >= 35.0F)
			{
				DrawText("WARNING", 420 + i * 5000, 125 + i * 5000, 20, WHITE);
			}
			else
			{
				DrawText(msjpayload, 420 + i * 5000, 125 + i * 5000, 20, WHITE);
			}
		}
		if (mensajes[i].topic.find("2/temperature"))
		{
			if (floatpayload >= 35.0F)
			{
				DrawText("WARNING", 420 + i * 5000, 185 + i * 5000, 20, WHITE);
			}
			else
			{
				DrawText(msjpayload, 420 + i * 5000, 185 + i * 5000, 20, WHITE);
			}
		}
		if (mensajes[i].topic.find("3/temperature"))
		{
			if (floatpayload >= 35.0F)
			{
				DrawText("WARNING", 420 + i * 5000, 245 + i * 5000, 20, WHITE);
			}
			else
			{
				DrawText(msjpayload, 420 + i * 5000, 245 + i * 5000, 20, WHITE);
			}
		}
		if (mensajes[i].topic.find("4/temperature"))
		{
			if (floatpayload >= 35.0F)
			{
				DrawText("WARNING", 420 + i * 5000, 305 + i * 5000, 20, WHITE);
			}
			else
			{
				DrawText(msjpayload, 420 + i * 5000, 305 + i * 5000, 20, WHITE);
			}
		}
	}

	// Conversion de imput a movimiento del robot
	bool success = moveRobot();

	// Parpadeo de los ojos del robot
	double time = GetTime();
	double period = time - (long)time;
	bool shouldLEDBeOn = (period < 0.1);
	if (isLEDOn != shouldLEDBeOn)
	{
		char redColor = shouldLEDBeOn ? 0xff : 0;
		vector<char> i = {redColor, 0, 0};
		cliente->publish("robot1/display/leftEye/set", i);
		cliente->publish("robot1/display/rightEye/set", i);
		isLEDOn = shouldLEDBeOn;
	}

	return success;
}

/*
 * Metodo que permite mover el robot
 * return: si se pudo mover el robot
 */
bool Controller::moveRobot(void)
{
	//Incluye para gamepad pero no lo pudimos probar pues no tenemos gamepad. Deberia funcionar
	int rotate = (IsKeyDown(KEY_A) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_TRIGGER_1)) 
				- (IsKeyDown(KEY_D) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_TRIGGER_1));

	int moveSideways = (IsKeyDown(KEY_RIGHT) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT)) 
						- (IsKeyDown(KEY_LEFT) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT));

	int moveForward = (IsKeyDown(KEY_UP) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_UP)) 
						- (IsKeyDown(KEY_DOWN) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN));

	// En la suma los resultados pueden ser distintos de 1, 0 o -1, pero no queremos aumentar la corriente en los motores
	int multiplicador1 = ((rotate + moveForward - moveSideways) == 0) ? 0 : ((rotate + moveForward - moveSideways) > 0) ? 1: -1;
	int multiplicador2 = ((rotate - moveForward - moveSideways) == 0) ? 0 : ((rotate - moveForward - moveSideways) > 0) ? 1: -1;
	int multiplicador3 = ((rotate - moveForward + moveSideways) == 0) ? 0 : ((rotate - moveForward + moveSideways) > 0) ? 1: -1;
	int multiplicador4 = ((rotate + moveForward + moveSideways) == 0) ? 0 : ((rotate + moveForward + moveSideways) > 0) ? 1: -1;

	// si se trata de una rotacion, utilizo un factor de escala menor
	float isrotation = (rotate == 0) ? 1.0F : 0.01F;

	bool success[4];
	success[0] = actualizarMotor(1, MOVE_CURRENT * multiplicador1 * isrotation);
	success[1] = actualizarMotor(2, MOVE_CURRENT * multiplicador2 * isrotation);
	success[2] = actualizarMotor(3, MOVE_CURRENT * multiplicador3 * isrotation);
	success[3] = actualizarMotor(4, MOVE_CURRENT * multiplicador4 * isrotation);

	bool tasksuccessfull = true;
	for(int i = 0; i < 4; i++)
	{
		if(!success[i])
		{
			tasksuccessfull = false;
		}
	}
	return tasksuccessfull;
}

/*
 * Metodo que actualiza la corriente en los motores del robot
 * param n: el numero del motor a actualizar
 * param current: la corriente que se le quiere dar al motor
 * return: si se pudo realizar la actualizacion 
 */
bool Controller::actualizarMotor(int n, float current)
{
	vector<char> i = getArrayFromFloat(current);
	bool success = cliente->publish("robot1/motor" + to_string(n) + "/current/set", i);
	
	return success;
}

/*
 * Metodo que permite dibujar la tabla
 */
void Controller::drawTable()
{
	DrawLine(40, 100, 540, 100, WHITE);
	DrawLine(40, 160, 540, 160, WHITE);
	DrawLine(40, 220, 540, 220, WHITE);
	DrawLine(40, 280, 540, 280, WHITE);
	DrawLine(95, 40, 95, 340, WHITE);
	DrawLine(245, 40, 245, 340, WHITE);
	DrawLine(395, 40, 395, 340, WHITE);

	DrawText("Nr", 40, 65, 25, WHITE);
	DrawText("1", 55, 125, 25, WHITE);
	DrawText("2", 55, 185, 25, WHITE);
	DrawText("3", 55, 245, 25, WHITE);
	DrawText("4", 55, 305, 25, WHITE);
	DrawText("Voltage", 125, 65, 25, WHITE);
	DrawText("Current", 260, 65, 25, WHITE);
	DrawText("Temperature", 400, 65, 25, WHITE);

	DrawText("Use arrows to move, [A] or [D] to turn", 50, 375, 14, WHITE);
}