KARŞIT MADDE LABİRENTİ

Bir labirent Lab[N][M] matrisi ile ifade edilmektedir. Labirentteki yollarda atomaltı parçacıklar vardır. Kullanıcı belirtilen giriş noktasından oyuna başlar ve çıkış noktasına doğru ilerler. Labirentin yollarından toplanan atomaltı parçacıklar kullanılarak karşıt hidrojen üretilecektir. Labirentte ilerlerken uyulması gereken kurallar ve labirentte bulunan parçacıklar aşağıda sıralanmıştır:
1.	Labirentteki yollarda aşağıdaki parçacıklar bulunmaktadır.
P+ 	: proton
e-	: elektron
P-	: karşıt proton
e+	: karşıt elektron
2.	Karşıt hidrojen üretebilmek için labirentin çıkışında elinizde sadece P- ve e+ parçacıkları bulunmalıdır. 
3.	Bir parçacıkla o parçacığın zıt işaretli karşıt parçacığı bir araya gelirse birbirini yok eder.
4.	Karadelikler K ile gösterilmiştir. Karadeliklerin bulunduğu hücrelerden geçildiği takdirde oyun sonlanır.
5.	Belirli bir oyun süresi içinde kullanıcı çıkışa ulaşamazsa oyun sonlanır.
6.	Oyun açıldığında kullanıcının hesap oluşturmasını ya da login olmasını sağlayan bir menü ekrana gelmelidir. Hesap oluşturma adımında kullanıcının isim, soy isim, kullanıcı adı ve şifre bilgileri alınacaktır. Aynı kullanıcı ismine sahip birden fazla kullanıcı olamaz. 
7.	Login adımında kullanıcının kullanıcı adı ve şifresi ile sisteme girmesi gerekmektedir.
8.	Kullanıcıyı oyuna ait en yüksek beş skor ve bu skorlara sahip kullanıcıların görüntülenmesini, oyunun nasıl oynanacağı hakkındaki bilgilerin görüntülenmesini ya da oyuna başlanmasını sağlayan bir menü karşılamalıdır.
9.	Oyun, kullanıcı kontrollü ve auto play modunda oynanabilmelidir. 
10.	Kullanıcı hazır haritalardan birini seçerek oynayabilmeli ya da istediği bir haritayı yükleyebilmelidir. Haritalar text dosya formatında tutulmalıdır.

Kullanıcı kontrolü modunda kullanıcının oyunu kendi istediği dört yöne giderek oynaması sağlanmalıdır. Labirentte gezinmek için ok tuşları kullanılacaktır. Karadelikler üzerine gelinirse oyun sonlanır. Kullanıcı oyunda x ile gösterilmelidir. Kullanıcının her hamlesinde ekran temizlenerek kullanıcının güncel lokasyonu x ile işaretlenmelidir. Duvarlara ve matris dışına hamle yapıldığında kullanıcının yeri değişmez. Kullanıcıya istediği zaman esc tuşuna basarak oyundan çıkma hakkı tanınmalıdır. Her hamle ile elde edilmiş atom altı parçacıklar ve labirentten çıkıldığında kaç karşıt madde üretildiği ekrana yazılmalıdır. 

Auto play modunda oyun, sizin belirlediğiniz bir algoritmayı kullanarak kendi kendine oynamalıdır. Yapılan her hamle sonunda oyun alanının son hali ve toplanan atom altı parçacıklar kullanıcı kontrolü modunda olduğu gibi yine ekrana yazılmalıdır. 
 
Labirentin elemanları aşağıdaki gibi gösterilmelidir. 
P+ 		: P		e-	: e		P-	: p		e+	: E	
Kara Delik	: K		Kullanıcı	: X		Cikis	: C		Yol	: 0	
Duvar		: 1		Giris	: G
