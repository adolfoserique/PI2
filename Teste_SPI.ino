const int SYNC_LASER = 7;
const int CS = 8;
const int CLK_SPI = 9;
const int MEIO_PER_CLK = 300;
const int PAUSE = 1000;

void setup() {
  pinMode(CS, OUTPUT);
  pinMode(CLK_SPI, OUTPUT);
  pinMode(SYNC_LASER, OUTPUT);
  digitalWrite(CS, HIGH);
  digitalWrite(CLK_SPI, LOW);
  digitalWrite(SYNC_LASER, HIGH);
}

void loop() {
  digitalWrite(SYNC_LASER, HIGH);
  delay(PAUSE);
  digitalWrite(SYNC_LASER, LOW);
  delayMicroseconds(10);
  digitalWrite(CS, HIGH);
  digitalWrite(CLK_SPI, LOW);
  delay(PAUSE);
  digitalWrite(CS, LOW);
  delay(PAUSE);
  digitalWrite(CLK_SPI, HIGH);
  delay(MEIO_PER_CLK);
  digitalWrite(CLK_SPI, LOW);
  delay(MEIO_PER_CLK);
  digitalWrite(CLK_SPI, HIGH);
  delay(MEIO_PER_CLK);
  digitalWrite(CLK_SPI, LOW);
  delay(MEIO_PER_CLK);
  digitalWrite(CLK_SPI, HIGH);
  delay(MEIO_PER_CLK);
  digitalWrite(CLK_SPI, LOW);
  delay(MEIO_PER_CLK);
  digitalWrite(CLK_SPI, HIGH);
  delay(MEIO_PER_CLK);
  digitalWrite(CLK_SPI, LOW);
  delay(MEIO_PER_CLK);
  digitalWrite(CLK_SPI, HIGH);
  delay(MEIO_PER_CLK);
  digitalWrite(CLK_SPI, LOW);
  delay(MEIO_PER_CLK);
  digitalWrite(CLK_SPI, HIGH);
  delay(MEIO_PER_CLK);
  digitalWrite(CLK_SPI, LOW);
  delay(MEIO_PER_CLK);
  digitalWrite(CLK_SPI, HIGH);
  delay(MEIO_PER_CLK);
  digitalWrite(CLK_SPI, LOW);
  delay(MEIO_PER_CLK);
  digitalWrite(CLK_SPI, HIGH);
  delay(MEIO_PER_CLK);
  digitalWrite(CLK_SPI, LOW);
  delay(MEIO_PER_CLK);
  delay(PAUSE);
  digitalWrite(CS, HIGH);
  delayMicroseconds(10);
}
