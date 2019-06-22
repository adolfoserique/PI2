const int CS = 8;
const int CLK_SPI = 9;
const int MEIO_PER_CLK = 1000;
const int PAUSE = 500;

void setup() {
  pinMode(CS, OUTPUT);
  pinMode(CLK_SPI, OUTPUT);
  digitalWrite(CS, HIGH);
  digitalWrite(CLK_SPI, LOW);
}

void loop() {
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
}
