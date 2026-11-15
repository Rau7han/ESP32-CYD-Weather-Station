# Estação meteorológica ESP32-CYD — Português brasileiro

Firmware para ESP32-CYD (Cheap Yellow Display), display TFT de 2,8 polegadas com toque resistivo XPT2046 e controlador ILI9341 (320 × 240).

> Esta é uma versão em desenvolvimento. A versão original foi preservada em [backup/upstream-v3.1](../../tree/backup/upstream-v3.1). A branch main é reservada a versões validadas.

## Funcionalidades

- Condições meteorológicas atuais via OpenWeather.
- Previsão de quatro dias com temperaturas mínima e máxima.
- Índice UV via Open-Meteo.
- Horário NTP, nascer e pôr do sol, fases da Lua e vento.
- Quatro telas: Início, Previsão, Condições e Sistema.
- Toque, gestos de deslizar, calibração e alternância automática.
- Recursos gráficos em LittleFS, conexão HTTPS e atualização automática.

## Hardware

- ESP32-WROOM-32 com flash de 4 MB.
- CYD ILI9341 320 × 240 e touch XPT2046.
- Rede Wi-Fi 2,4 GHz e alimentação USB.

O ST7789 possui arquivo de configuração de referência, mas ainda não foi testado nesta adaptação.

## VS Code + PlatformIO

1. Instale o [Visual Studio Code](https://code.visualstudio.com/) e a extensão **PlatformIO IDE**.
2. Clone este repositório e abra sua pasta raiz no VS Code.
3. Copie `Esp32_CYD_TFT_eSPI_OpenWeather_LittleFS_v02/Secrets.example.h` para `Secrets.h`, na mesma pasta, e configure o SSID, senha e chave da API OpenWeather.
4. Em `All_Settings.h`, configure cidade, latitude, longitude e fuso no formato POSIX. O exemplo fornecido usa Sorocaba/SP, com `BRT3` (UTC−3).
5. Execute **PlatformIO: Build** e **Upload**.
6. Execute **PlatformIO: Upload Filesystem Image** para gravar as fontes, ícones e demais recursos da pasta `data/` no LittleFS.
7. Abra o monitor serial a **115200 baud** e reinicie o ESP32.

O arquivo `platformio.ini` utiliza pioarduino **54.03.20**, correspondente ao Arduino ESP32 Core **3.2.0**, preservando a versão usada pelo projeto original.

## Organização das branches

- `backup/upstream-v3.1`: versão original preservada.
- `feature/pt-br-platformio`: tradução e migração em andamento.
- `develop`: integração após revisão.
- `main`: versão funcional e homologada.

## Pendências de validação

- Compilar no PlatformIO e revisar os resultados do GitHub Actions.
- Testar a inicialização, touch, LittleFS, NTP e HTTPS na placa real.
- Verificar caracteres acentuados das fontes VLW e revisar os textos mais longos na tela.
- Completar a centralização das mensagens traduzidas.

O projeto original é de [Rau7han](https://github.com/Rau7han/ESP32-CYD-Weather-Station). Licença MIT e avisos de terceiros foram preservados.
