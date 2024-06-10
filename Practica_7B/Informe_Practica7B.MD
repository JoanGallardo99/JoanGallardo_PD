# PRACTICA 7B:  Buses de comunicación III (I2S)  
## Análisis del código
Este código está diseñado para crear una radio web en un ESP32, que permite al usuario controlar la reproducción de audio en streaming a través de una interfaz web.
1. Inclusions y definiciones de preprocesador
2. Inclusión de bibiliotecas específicas
   - Se incluyen bibliotecas especipfics para Wifi y audio.
3. Declaración de funciones y variables globales
   - Se declaran las funciones que se usarán para redicreccionar, cargar y guardar configuraciones
    ```c
    void RedirectToIndex(WiFiClient *client);
    void LoadSettings();
    void SaveSettings();
    ```
    - Se declaran variables globales para la configuración WiFI, el servidor y las fuentes y salidas de audio. También se definen variables para gestionar el estado del reproductor de audio.
4. Estrucutra de configuración
   - Se define una estructura para guardar la configuración del reproductor (URL, tipo de audio, volumen y un checksum para verificación).
5. HTML y JavaScript Embebido
6. Manejo de solicitudes web
   - ```c
        void HandleIndex(WiFiClient *client)
        {
        char buff[sizeof(BODY) + sizeof(title) + sizeof(status) + sizeof(url) + 3*2];
        WebHeaders(client, NULL);
        WebPrintf(client, DOCTYPE);
        client->write_P(PSTR("<html>"), 6);
        client->write_P(HEAD, strlen_P(HEAD));
        sprintf_P(buff, BODY, title, volume, volume, status, url);
        client->write(buff, strlen(buff));
        client->write_P(PSTR("</html>"), 7);
        }

        void HandleStatus(WiFiClient *client)
        {
        WebHeaders(client, NULL);
        client->write(status, strlen(status));
        }

        void HandleTitle(WiFiClient *client)
        {
        WebHeaders(client, NULL);
        client->write(title, strlen(title));
        }

        void HandleVolume(WiFiClient *client, char *params)
        {
        char *namePtr;
        char *valPtr;
        while (ParseParam(&params, &namePtr, &valPtr)) {
            ParamInt("vol", volume);
        }
        out->SetGain(((float)volume)/100.0);
        RedirectToIndex(client);
        }

        void HandleChangeURL(WiFiClient *client, char *params)
        {
        char *namePtr;
        char *valPtr;
        char newURL[sizeof(url)];
        char newType[4];

        newURL[0] = 0;
        newType[0] = 0;
        while (ParseParam(&params, &namePtr, &valPtr)) {
            ParamText("url", newURL);
            ParamText("type", newType);
        }
        if (newURL[0] && newType[0]) {
            newUrl = true;
            strncpy(url, newURL, sizeof(url)-1);
            url[sizeof(url)-1] = 0;
            if (!strcmp_P(newType, PSTR("aac"))) {
            isAAC = true;
            } else {
            isAAC = false;
            }
            strcpy_P(status, PSTR("Changing URL..."));
            RedirectToIndex(client);
        } else {
            WebError(client, 404, NULL, false);
        }
        }

        void HandleStop(WiFiClient *client)
        {
        StopPlaying();
        RedirectToIndex(client);
        }
        ```
    - Estas funciones manejan las solicitudes web recibidas por el servidor. Cada función maneja un tipo específico de solicitud, como la actualización del título, estado, volumen, cambio de URL y detención de la reproducción.
7. Funciones de decodificación y reproducción
   - ```c
        void MDCallback(void *cbData, const char *type, bool isUnicode, const char *str)
        {
        if (strstr_P(type, PSTR("Title"))) {
            strncpy(title, str, sizeof(title));
            title[sizeof(title)-1] = 0;
        }
        }

        void StatusCallback(void *cbData, int code, const char *string)
        {
        strncpy_P(status, string, sizeof(status)-1);
        status[sizeof(status)-1] = 0;
        }

        #ifdef ESP8266
        const int preallocateBufferSize = 5*1024;
        const int preallocateCodecSize = 29192; 
        #else
        const int preallocateBufferSize = 16*1024;
        const int preallocateCodecSize = 85332; 
        #endif

        void *preallocateBuffer = NULL;
        void *preallocateCodec = NULL;

        void StopPlaying()
        {
        if (decoder) {
            decoder->stop();
            delete decoder;
            decoder = NULL;
        }
        if (buff) {
            buff->close();
            delete buff;
            buff = NULL;
        }
        if (file) {
            file->close();
            delete file;
            file = NULL;
        }
        strcpy_P(status, PSTR("Stopped"));
        strcpy_P(title, PSTR("Stopped"));
        }

        void StartNewURL()
        {
        newUrl = false;
        StopPlaying();
        SaveSettings();
        file = new AudioFileSourceICYStream(url);
        file->RegisterMetadataCB(MDCallback, NULL);
        buff = new AudioFileSourceBuffer(file, preallocateBuffer, preallocateBufferSize);
        buff->RegisterStatusCB(StatusCallback, NULL);
        decoder = isAAC ? (AudioGenerator*) new AudioGeneratorAAC(preallocateCodec, preallocateCodecSize) : (AudioGenerator*) new AudioGeneratorMP3(preallocateCodec, preallocateCodecSize);
        decoder->RegisterStatusCB(StatusCallback, NULL);
        decoder->begin(buff, out);
        strcpy_P(status, PSTR("Playing"));
        strcpy_P(title, PSTR("Starting"));
        }

        void PumpDecoder()
        {
        if (decoder && decoder->isRunning()) {
            if (!decoder->loop()) {
            StopPlaying();
            retryms = millis() + 5000;
            }
        } else {
            if (retryms && millis() > retryms) {
            retryms = 0;
            newUrl = true;
            }
        }
        }
        ```
    - Estas funciones gestionan el inicio y detención de la reproducción de audio. StartNewURL configura una nueva URL para streaming y comienza la reproducción. StopPlaying detiene cualquier reproducción en curso. PumpDecoder se llama repetidamente para mantener la reproducción en marcha.
8. Funciones para redireccionar y manejar cabeceras web
9. Funciones para cargar y guardar configuraciones
10. Función Setup
11. Función Loop
    - Comprobar y actualizar el estado de la conexión WiFi
    - Comprobar si hay nuevas URL's para reproducir
    - Mantener la reproducción en marcha
    - Manejar las coneciones entrantes al servidor



    