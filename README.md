# Smart Pill Dispenser (Client)

Arduino 側のクライアントコード。
Wi-Fi 経由でサーバーと TCP 接続し、サーバーから送られてくる指示に従って指定時刻に薬を排出する。

サーバーリポジトリ：https://github.com/Tkino117/pill-dispenser-server

## 概要

- サーバーと常時接続し、`dispense` コマンドを受信するとサーボを回して薬を排出する
- 薬排出時は LED 点灯 + ブザー鳴動でユーザーに通知する
- 光センサーで薬が取られたことを検知し、サーバーに `take pill` を通知する
- 3 スロット(A / B / C)まで対応し、薬の種類ごとに独立して排出できる

## ハードウェア構成

| 要素 | ピン | 備考 |
|------|------|------|
| サーボ A | D9  | スロット 1 用 |
| サーボ B | D10 | スロット 2 用 |
| サーボ C | D11 | スロット 3 用 |
| 光センサー | D5 | 薬の取り出し検知 |
| LED | D3 | 排出時に点灯 |
| ブザー | D4 | 排出時に鳴動 |
| LED マトリクス | 内蔵 | メッセージ表示 |

対応ボード: Arduino UNO R4 WiFi(`WiFiS3` および `Arduino_LED_Matrix` ライブラリを使用)

## ファイル構成

```
client/
├── main/
│   ├── main.ino       メインスケッチ。loop で送受信とコマンド実行
│   ├── main.h         サーバーの host / port 設定
│   ├── wifi.h/.cpp    Wi-Fi 接続処理 (SSID / パスワード設定)
│   └── led_mat.h/.cpp LED マトリクス制御
```

## 通信プロトコル

TCP テキストベース。各メッセージは `\r` で区切られる。

### サーバー → Arduino

| コマンド | 説明 |
|----------|------|
| `dispense <id> <count>` | スロット `id` (1-3) から `count` 個の薬を排出 |
| `servo <id> <deg>` | サーボ `id` を `deg` 度回転(調整用) |

### Arduino → サーバー

| メッセージ | 説明 |
|-----------|------|
| `take pill` | 光センサーが薬の取り出しを検知したとき送信 |

## セットアップ

1. `main/wifi.h` の `ssid` / `pass` を自宅ネットワークに合わせて書き換える
2. `main/main.h` の `host` / `port` をサーバーの IP / ポートに設定する
3. Arduino IDE で `main/main.ino` を開き、ボードに書き込む
4. シリアルモニタ(115200 bps)で接続ログを確認する
