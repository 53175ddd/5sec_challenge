#define OFFSET -10  // クロックの誤差調整用 / 適宜調整 / わからなければ 0 でよし

uint16_t counter   = 0;
uint8_t  sw_status = 0;

ISR(TIMER1_COMPA_vect) {
  PORTD = PORTD | 0b00000100;  // D2 を HIGH に

  sw_status = (sw_status << 1) + ((((PIND & 0b00001000) >> 3) == 0) ? 1 : 0);// D3 を読み取りステータス変数を更新

  if((sw_status & 0b00000011) == 0b01) {  // スイッチ押されたとき
    clear();  // ディスプレイの表示を消す
    counter = 1;
  }

  if(((PIND & 0b00001000) >> 3) == 0) {   // スイッチが押されている間
    counter++;
    if(counter > 9999) {
      counter = 9999;
    }
  }

  if((sw_status & 0b00000011) == 0b10) {  // スイッチ放されたとき
    output(counter);  // 結果を表示
  }

  PORTD = PORTD & 0b11111011;  // D2 を LOW に
}

void setup() {
  TCCR1A = 0;                           // タイマー 1 動作モードを初期化
  TCCR1B = (1 << WGM12) | (1 << CS10);  // CTC モード 分周比 1
  OCR1A  = 16000 - 1 + OFFSET;          // 1kHz となるように設定
  TIMSK1 = (1 << OCIE1A);               // タイマー 1 の A マッチ割り込みを許可

  DDRD = DDRD | 0b00000100;  // D2 を出力に

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

  Serial.print(a);
  Serial.print(b);
  Serial.print(c);
Serial.print(d    );
  Serial.println(" ms");
}

void clear(void) {
}
