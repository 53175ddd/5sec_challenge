#define OFFSET 0  // クロックの誤差調整用 / 適宜調整 / わからなければ 0 でよし

#define SW A3

#define LATCH 2
#define DOUT  4
#define CLK   3

uint16_t counter   = 0;
uint8_t  sw_status = 0;

uint8_t font[] = {0b11111100, 0b01100000, 0b11011010, 0b11110010, 0b01100110, 0b10110110, 0b10111110, 0b11100000, 0b11111110, 0b11110110};

ISR(TIMER1_COMPA_vect) {
  sw_status = (sw_status << 1) + ((digitalRead(SW) == 0) ? 1 : 0);  // D3 を読み取りステータス変数を更新

  if((sw_status & 0b00000011) == 0b01) {  // スイッチ押されたとき
    clear();  // ディスプレイの表示を消す
    counter = 1;
  }

  if(digitalRead(SW) == LOW) {   // スイッチが押されている間
    counter++;
    if(counter > 9999) {
      counter = 9999;
    }
  }

  if((sw_status & 0b00000011) == 0b10) {  // スイッチ放されたとき
    output(counter);  // 結果を表示
  }
}

void setup() {
  pinMode(SW   ,  INPUT_PULLUP);
  pinMode(LATCH, OUTPUT);
  pinMode(DOUT , OUTPUT);
  pinMode(CLK  , OUTPUT);

  digitalWrite(LATCH, HIGH);

  digitalWrite(LATCH,  LOW);
  delayMicroseconds(10);
  shiftOut(DOUT, CLK, LSBFIRST, 0xff);
  shiftOut(DOUT, CLK, LSBFIRST, 0xff);
  shiftOut(DOUT, CLK, LSBFIRST, 0xff);
  shiftOut(DOUT, CLK, LSBFIRST, 0xff);
  delayMicroseconds(10);
  digitalWrite(LATCH, HIGH);

  delay(1000);

  digitalWrite(LATCH,  LOW);
  delayMicroseconds(10);
  shiftOut(DOUT, CLK, LSBFIRST, 0x00);
  shiftOut(DOUT, CLK, LSBFIRST, 0x00);
  shiftOut(DOUT, CLK, LSBFIRST, 0x00);
  shiftOut(DOUT, CLK, LSBFIRST, 0x00);
  delayMicroseconds(10);
  digitalWrite(LATCH, HIGH);

  delay(1000);

  digitalWrite(LATCH,  LOW);
  delayMicroseconds(10);
  shiftOut(DOUT, CLK, LSBFIRST, font[0]);
  shiftOut(DOUT, CLK, LSBFIRST, font[0]);
  shiftOut(DOUT, CLK, LSBFIRST, font[0]);
  shiftOut(DOUT, CLK, LSBFIRST, font[0] + 1);
  delayMicroseconds(10);
  digitalWrite(LATCH, HIGH);

  TCCR1A = 0;                           // タイマー 1 動作モードを初期化
  TCCR1B = (1 << WGM12) | (1 << CS10);  // CTC モード 分周比 1
  OCR1A  = 16000 - 1 + OFFSET;          // 1kHz となるように設定
  TIMSK1 = (1 << OCIE1A);               // タイマー 1 の A マッチ割り込みを許可

  Serial.begin(115200);
}

void loop() {
}

void output(const uint16_t raw) {
  uint16_t counter = raw;
  int8_t a, b, c, d;

  d = counter % 10;
  counter = (counter - d) / 10;

  c = counter % 10;
  counter = (counter - c) / 10;

  b = counter % 10;
  counter = (counter - b) / 10;

  a = counter;

  digitalWrite(LATCH,  LOW);
  delayMicroseconds(10);
  shiftOut(DOUT, CLK, LSBFIRST, font[d]);
  shiftOut(DOUT, CLK, LSBFIRST, font[c]);
  shiftOut(DOUT, CLK, LSBFIRST, font[b]);
  shiftOut(DOUT, CLK, LSBFIRST, font[a] + 1);
  delayMicroseconds(10);
  digitalWrite(LATCH, HIGH);

  Serial.print(a);
  Serial.print(b);
  Serial.print(c);
  Serial.print(d);
  Serial.print(" ms\n");
}

void clear(void) {
  digitalWrite(LATCH,  LOW);
  for(size_t i = 0; i < 4; i++) {
    shiftOut(DOUT, CLK, LSBFIRST, 0);
  }
  digitalWrite(LATCH, HIGH);
}
