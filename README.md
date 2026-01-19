🌡️ TelemetryMonitor: Adquisición de Datos y Graficado en Tiempo Real
Sistema de Monitoreo Térmico con Qt, Arduino y MySQL

Este proyecto permite la adquisición de señales analógicas desde un microcontrolador (Arduino) para su procesamiento, almacenamiento y visualización gráfica. El sistema convierte lecturas de ADC en variables físicas (Voltaje y Temperatura) y las gestiona mediante una base de datos robusta.

🚀 Funcionalidades Principales
Comunicación Serial Asíncrona: Conexión automática con dispositivos Arduino/MEGA mediante detección de VID/PID.

Protocolo JSON: Decodificación de mensajes JSON entrantes para una transferencia de datos estructurada y segura.

Historial en Base de Datos: Registro de lecturas con Timestamps UNIX en MySQL para auditoría y análisis posterior.

Visualización Dinámica: Implementación de QCustomPlot para generar gráficas de tendencia de los últimos 20 registros.

Conversión de Ingeniería: Cálculo preciso de temperatura basado en la curva característica del sensor.

🛠️ Stack Tecnológico
C++ / Qt Framework: Uso de módulos SerialPort, Sql y Network.

QCustomPlot: Librería avanzada para el renderizado de gráficas 2D.

MySQL: Motor de base de datos para la persistencia de datos.

Arduino: Firmware encargado de la lectura del sensor y envío de tramas JSON.
![Graficador](https://github.com/user-attachments/assets/15c463f3-2055-4439-a87d-7fcb0406fc98)

🇺🇸 English Version (README.md)
🌡️ TelemetryMonitor: Real-Time Data Acquisition & Plotting
Thermal Monitoring System with Qt, Arduino, and MySQL

This project enables the acquisition of analog signals from a microcontroller (Arduino) for processing, storage, and graphical visualization. The system converts ADC readings into physical variables (Voltage and Temperature) and manages them through a robust database.

🚀 Key Features
Asynchronous Serial Communication: Automatic connection to Arduino/MEGA devices using VID/PID detection.

JSON Protocol: Decodes incoming JSON messages for structured and secure data transfer.

Database Logging: Records readings with UNIX Timestamps in MySQL for auditing and historical analysis.

Dynamic Visualization: Integrated QCustomPlot to generate trend graphs for the last 20 records.

Engineering Conversion: Precise temperature calculation based on the sensor's characteristic curve.

🛠️ Tech Stack
C++ / Qt Framework: Utilizing SerialPort, Sql, and Network modules.

QCustomPlot: Advanced library for 2D plot rendering.

MySQL: Database engine for data persistence.

Arduino: Firmware responsible for sensor reading and JSON transmission.
