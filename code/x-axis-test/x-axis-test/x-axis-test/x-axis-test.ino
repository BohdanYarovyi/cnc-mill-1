const char STEP_PIN						=  3;
const char DIR_PIN						=  2;
const char BTN_PLUS_PIN					=  4;
const char MS1_PIN						=  8;
const char MS2_PIN						=  9;
const char MS3_PIN						= 10;
const char ENABLE_PIN					= 11;
const char BUILTIN_LED_PIN				= 13;

bool is_done = false;

void rotate_rotor(const bool direction, const int delay_ms, const long long steps)
{
	digitalWrite(ENABLE_PIN, LOW);
	digitalWrite(DIR_PIN, direction ? HIGH : LOW);

	for (long long s = 0; s < steps; s++)
	{
		digitalWrite(STEP_PIN, HIGH);
		delayMicroseconds(2);
		digitalWrite(STEP_PIN, LOW);
		delayMicroseconds(delay_ms);
	}
	digitalWrite(ENABLE_PIN, HIGH);
}

void after_init_pause()
{
	digitalWrite(BUILTIN_LED_PIN,	HIGH);
	delay(1000);
	digitalWrite(BUILTIN_LED_PIN,	LOW);
	delay(1000);

	digitalWrite(BUILTIN_LED_PIN,	HIGH);
	delay(200);
	digitalWrite(BUILTIN_LED_PIN,	LOW);
	delay(200);
	digitalWrite(BUILTIN_LED_PIN,	HIGH);
	delay(200);
	digitalWrite(BUILTIN_LED_PIN,	LOW);
	delay(200);
	digitalWrite(BUILTIN_LED_PIN,	HIGH);
	delay(200);
	digitalWrite(BUILTIN_LED_PIN,	LOW);
	delay(200);
}

void setup()
{
	pinMode(BUILTIN_LED_PIN,		OUTPUT);
	pinMode(STEP_PIN,				OUTPUT);
	pinMode(DIR_PIN,				OUTPUT);
	pinMode(MS1_PIN,				OUTPUT);
	pinMode(MS2_PIN,				OUTPUT);
	pinMode(MS3_PIN,				OUTPUT);
	pinMode(ENABLE_PIN,				OUTPUT);
	pinMode(BUILTIN_LED_PIN,		OUTPUT);

	pinMode(BTN_PLUS_PIN,			INPUT_PULLUP);

	digitalWrite(STEP_PIN,			LOW);
	digitalWrite(DIR_PIN,			LOW);
	digitalWrite(BUILTIN_LED_PIN,	LOW);

	digitalWrite(MS1_PIN,			HIGH);
	digitalWrite(MS2_PIN,			HIGH);
	digitalWrite(MS3_PIN,			HIGH);
	digitalWrite(ENABLE_PIN,		HIGH);

	after_init_pause();
}

bool direction = true;

void loop()
{
	if (!is_done) {
		int delay_ms = 600;
		long long steps = (static_cast<long long>(3200) / 8) * 100;
		int offset = 20;
		int rotates = 20;
		
		rotate_rotor(direction, delay_ms, steps);
		is_done = true;
	}

	int btn_val = digitalRead(BTN_PLUS_PIN);
	if (is_done && btn_val == LOW)
	{
		is_done = false;
		direction = ! direction;
	}
}