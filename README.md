# 5sec_challenge

[#5sec_challenge](https://x.com/hashtag/5sec_challenge) とは：あなたの体内時計がどれほど正確か / いい加減かを試すことができる挑戦です

# 組み立て例

こんな感じに組み上がります．  
Arduino Nano は互換品を使っています．

![IMG_20250211_054828145](https://github.com/user-attachments/assets/8ee0f128-84c2-4e35-b180-2c420f2476c5)

# Booth 販売ページ

<https://nch-mosfet.booth.pm/items/6582794>

こんなのが届きます．

![IMG_20250211_054746937](https://github.com/user-attachments/assets/210a54ce-cc63-462d-bcfc-2a5c05b8de12)

これに追加で，Arduino Nano をご用意下さい．Amazon で買える適当なもので大丈夫です．

# 簡易組み立て手順書

1. 部品をはんだ付けする
2. Arduino Nano にプログラムを書き込む
3. 組み上げる
4. 動かす

## 部品をはんだ付けする

基本的にフットプリントの通りのものをはんだ付けして行きます．  
向きは下の画像を参考にして下さい．C1 / C2 については，C1 が 104，C2 が 224 です．

![IMG_20250211_054859264](https://github.com/user-attachments/assets/6f6f2d3e-e734-4601-83fa-37fc3d10005f)
![IMG_20250211_055154663](https://github.com/user-attachments/assets/1e1c822b-6d14-4608-97b4-b3b653e2825e)

## Arduino Nano にプログラムを書き込む

適合する USB ケーブルを使って PC に接続し，[5sec_challenge.ino](./5sec_challenge.ino) を書き込んで下さい．

## 組み上げる

トップ画像を参考に組み上げて下さい．スイッチを接続するかは任意です．

## 動かす

電源（USB または DC9 ~ 12V）を接続し，スイッチ（SW1）をぽちぽちしてください．結果が表示されます．  
その後，スイッチ（SW1）を押しながら Arduino Nano をリセットし，サブモードで起動させて下さい．スイッチを長押しして，タイムが常時表示されるようになれば動作確認完了です．

# 遊び方

友達や家族，知り合いなどと一緒に，誰が一番 5.000 秒に近いスコアを出せるかを勝負するもよし，一人で黙々とトライするもよし，9.999 秒までしか測れないストップウォッチとして使うもよし（？）  
結果はぜひ [#5sec_challenge](https://x.com/hashtag/5sec_challenge) を添えてツイートしてください．
