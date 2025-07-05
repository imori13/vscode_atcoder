# AtCoder Development Environment

MinGW64環境を含むDockerベースのAtCoder開発環境です。

## 機能

- **クロスプラットフォーム対応**: Linux/Windows両方の実行ファイルを生成可能
- **MinGW64**: Windows実行ファイルを生成
- **AtCoder Library**: ACL自動インストール済み
- **統一開発環境**: Docker環境により環境差を解消
- **VSCode統合**: F5キーでワンクリック実行

## 使用方法

### VSCode統合

`.vscode/tasks.json`と`.vscode/launch.json`が設定済み：
- **F5**: ビルド＆実行（input.txtを標準入力として使用）
- **Ctrl+Shift+P** → "Tasks: Run Task" → "Build with Docker"でビルドのみ
- **Ctrl+Shift+P** → "Tasks: Run Task" → "Run with input"で実行のみ

### 手動Docker操作

```bash
# コンテナ起動
docker-compose up -d

# コンテナ内でビルド
docker-compose exec atcoder g++ -std=c++17 -O2 main.cpp -o output/main

# MinGW64でビルド
docker-compose exec atcoder x86_64-w64-mingw32-g++ -std=c++17 -O2 main.cpp -o output/main.exe

# 実行（標準入力付き）
docker-compose exec -T atcoder bash -c "./output/main < input.txt"
```

## ディレクトリ構成

```
vscode_atcoder/
├── .vscode/
│   ├── tasks.json      # ビルドタスク設定
│   └── launch.json     # デバッグ設定
├── output/             # 実行ファイル出力先
├── Dockerfile          # Docker環境定義
├── docker-compose.yml  # Docker Compose設定
├── run_docker.js       # Node.js実行ランチャー
├── input.txt          # テスト入力
└── main.cpp           # ソースファイル
```

## 環境変数

コンテナ内で以下の環境変数が設定されます：

- `CC=gcc`
- `CXX=g++`
- `MINGW_CC=x86_64-w64-mingw32-gcc`
- `MINGW_CXX=x86_64-w64-mingw32-g++`

## トラブルシューティング

### Docker関連
- Docker Desktopが起動していることを確認
- `docker-compose down && docker-compose up -d --build`で再構築

### ビルドエラー
- `output/`ディレクトリが存在することを確認
- AtCoder Libraryを使用する場合は`#include <atcoder/all>`を使用

### Windows実行ファイル
- MinGW64でビルドしたファイルはWindows環境で実行可能
- コンテナ内でWineを使用してテスト実行も可能

### VSCode実行エラー
- Node.jsがインストールされていることを確認
- Docker環境が正常に起動していることを確認