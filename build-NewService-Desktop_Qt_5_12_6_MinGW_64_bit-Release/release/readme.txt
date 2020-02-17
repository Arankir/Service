проверить службу в консоли: Service.exe -e
создать службу: sc create "ArankirService" binpath="C:\Users\Pavel\Desktop\All\Projects\Service\Service\build-NewService-Desktop_Qt_5_12_6_MinGW_64_bit-Release\release\Service.exe" start=auto
удалить службу: sc delete "ArankirService"
консоль запускать от админа