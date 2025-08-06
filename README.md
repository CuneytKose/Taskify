# Taskify
To do list
Terminal üzerinden çalışan basit bir görev yöneticisi.

C++ öğrenme sürecimde yazdığım, küçük ama kalıcı verilerle çalışan bir to-do uygulaması.  
Görev ekleyip, listeleyip tamamlandığında işaretleyebiliyorsunuz. Hepsi `tasks.txt` dosyasına kaydediliyor.

##  Derleme

g++ Taskify.cpp -o Taskify

görev ekleme
./Taskify add "Sunucuları güncelle"

Görevleri listeleme
./Taskify list

örnek
1 - Sunucuları güncelle [Pending]

Görevi tamamlandı olarak işaretleme
./Taskify done 1

Tüm görevler tasks.txt dosyasında tutulur.
Program her çalıştırıldığında bu dosya güncellenir.
