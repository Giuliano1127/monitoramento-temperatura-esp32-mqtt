# Monitoramento de Temperatura com ESP32 + MQTT + Node-RED

Este projeto simula o monitoramento de temperatura usando um ESP32, um sensor NTC e comunicação MQTT com visualização via Node-RED.

## Tecnologias utilizadas

- ESP32 (simulado via [Wokwi](https://wokwi.com/projects/433410198946661377))
- Sensor NTC 10k
- MQTT (broker HiveMQ)
- Node-RED (dashboard local)
- C

## Funcionamento

- O ESP32 lê a temperatura via sensor NTC conectado ao ADC.
- A leitura é convertida com a equação Beta.
- A temperatura é publicada a cada 5 segundos no tópico MQTT:
- O Node-RED consome esse tópico e exibe a leitura em tempo real.

## Capturas de tela
![Esp32+MQTT](https://github.com/user-attachments/assets/6a80f761-e5b1-4603-a430-7114ce9938ab)
![Fluxo Node_Red](https://github.com/user-attachments/assets/7e6c02c0-d44a-4f22-81e6-c1386f6b8530)
![Esp32+MQTT](https://github.com/user-attachments/assets/2a343a8c-3295-43b2-af4d-6a004918912c)
## Como executar

 Clone este repositório.
 Acesse o projeto no Wokwi.
 Instale o Node-RED localmente e importe o fluxo `node-red/fluxo-node-red.json`.
 Configure o nó MQTT-IN com o broker `broker.hivemq.com` e porta `1883`.
