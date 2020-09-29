проверить службу в консоли: Service.exe -e
создать службу: sc create "ArankirService" binpath="C:\Users\RUSLANoffice\Desktop\All\Projects\Service\build-NewService-Desktop_Qt_5_14_2_MinGW_64_bit-Release\release\Service.exe" start=auto
удалить службу: sc delete "ArankirService"
консоль запускать от админа