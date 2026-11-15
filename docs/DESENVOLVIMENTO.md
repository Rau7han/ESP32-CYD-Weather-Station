# VS Code / PlatformIO

Abra a raiz no VS Code com PlatformIO IDE. Copie `Secrets.example.h` para `Secrets.h` dentro da pasta do sketch, configure Wi-Fi e chave OpenWeather. Ajuste o local e fuso em `All_Settings.h` (padrao Sorocaba/SP, BRT3). Compile com PlatformIO Build, faca Upload e depois Upload Filesystem Image para LittleFS. Monitor serial: 115200 baud.

Hardware-alvo: CYD ESP32-WROOM-32, ILI9341 320x240, touch XPT2046 e flash 4 MB.

Fluxo de branches: `backup/upstream-v3.1` original; `feature/pt-br-platformio` desenvolvimento; `develop` integracao; `main` somente apos testes.

Pendente: validar build PlatformIO real, suporte a acentos nas fontes VLW e testes em hardware. As labels da tela usam ASCII ate validacao dos glifos.
