#AutoPlan
==================

AUTOPLAN

ADI SOYADI			: GÜRSU AŞIK

PROJENİN ADI 			: AUTOPLAN

PROJENİN KONUSU		: ELEKTRİK TESİSAT ÇİZİM PROGRAMI

PROJENİN AMACI		: Bilgisayar ortamında mimari projeden otomatik olarak elektrik tesisat projesini çizdirmek.

PROJENİN HEDEFLERİ		: Bilgisayar ortamında mimari projeden elektrik tesisat projesini çizdirip, zamandan tasarruf sağlamak.

PROJENİN MALİYETİ		: Sıfır maliyet

PROJENİN SÜRESİ 		: 4 Ay

PROJENİN SONUÇLARI	: Elektrik tesisat projeleri üzerine çalışan insanların işlerini kolaylaştırmak, çizimde insan hatalarından kaynaklanan yanlışlıkların önüne geçmek.

KAYNAKÇA			: Elektrik-Elektronik Tek. alanı aydınlatma projeleri modülü.

   Şimdi Microsoft Visual C++ Öğrenin (Chuck Sphar) kitabı.
   
   
   PROJENİN ÇALIŞMASI HAKKINDA GENEL BİLGİLER

Bu projede kat planı çizilen binanın, elektrik tesisat planını otomatik olarak çizebilecek bir yazılım geliştirmeye çalıştım. Böyle bir program kullanıcılara rahatlık sağlar ve önemli oranda zaman kazandırabilir.

Bu programın çalışabilmesi kat planından çıkarabileceği ipuçlarıyla mümkün olabilir. Kat planları aydınlatma projeleri için önemli ayrıntılara sahip olabiliyor. Örnek olarak:
•	Bu kat planında odalara yerleştirilecek lambalar zaten odaların orta noktalarına yerleştirilecektir.
•	Bu lambalar için kullanılacak anahtarların oda girişlerine yakın noktalara ve kapılar açıldığında kapıların arakasında kalmayacak şekilde (kapı açıklığından 40 cm mesafede) yerleşmesi gerektiğinden kat planı anahtar konumları bilgilerini de verir. 
•	Prizler de anahtarlar için konabilecek yerler de dahil oda duvarlarının uygun değişik noktalarına hazırlanan program tarafından konabilir.

•	Kat planlarında banyo ve tuvalet gibi bölmeler de belirtildiğinden program tarafından elde edilen bu bilgiler sayesinde buralara yerleştirilecek lamba ve prizlerin farkı yine program tarafından çizilen aydınlatma projesinde belirtilebilir.
•	Kat planlarında mutfak tezgâhı, banyo küveti, lavabo gibi gösterilen ayrıntılarla beraber programın nerelere priz koyması ya da kesinlikle koymaması gerektiği bilgisi program tarafından kat planından elde edilebilir. Böylece programın aydınlatma projesine katkısı daha da fazla olabilir.

Zamanın kısıtlı olması sebebiyle; diğer ürünler yanında tercih edilebilecek ve rahat kullanılabilecek bir ürün hazırlayamasam da, böyle bir programın geliştirilebilmesine yönelik fikirlerimin uygulanabilirliğini gösteren bir program hazırladım.

Kat Planı verildiğinde Aydınlatma projesini otomatik olarak çizdiğinden programa AutoPlan adını verdim.
Program Windows XP ve üzeri işletim sistemlerinde çalışabiliyor.
Kat planlarının yine bu program arayüzünde çizilmesi gerekiyor.
Duvar, kapı, pencere ve kolon çizimine izin veriliyor.
Merdiven, mutfak, banyo tuvalet ve balkon ayrımına şimdilik izin vermiyor. Fakat programa yapılacak ilavelerle aynı algoritmalar temel alınarak bu ayrıma göre planın çizilmesi sağlanabilir.
Program çok katlı binaların çizimine imkân verebiliyor.

Programı kısa bir zaman diliminde hazırlamak zorunda olduğumdan bazı kısıtlayıcı şartlar altında çalışabilecek bir program hazırlayabilirdim. Bu program da şu tür yetersizliklere sahip.

•	Tasarlanan algoritmaların yetersizliklerinden kaynaklanan kısıtlayıcıların olması
•	Kullanıcı arayüzünün yetersizliklerinden kaynaklanan kısıtlayıcıların olması
•	Gizlenmemiş ya da engellenmemiş doğal kısıtlayıcıların olması

TASARLANAN ALGORİTMALARIN YETERSİZLİKLERİNDEN KAYNAKLANAN KISITLAYICILAR

Gerekli algoritmaları ve bunların uygulamasını daha kısa sürede gerçekleştirebilmek için bazı özel durumları dikkate almadım. Algoritmaların daha geniş perspektiften bakarak tasarlanmaması bazı kısıtlamaları beraberinde getiriyor. Örneğin:
•	Kat planlarında sadece düz duvarların olabileceğini kabul ettim. Çembersel duvarların olabileceği ihtimalini göz ardı ettim. Kullanıcı arayüzünde bunun için gerekli araç çubuğu düğmesine de yer vermedim.
•	Algoritmaları bir oda içinde başka bir odanın olmayacağını kabul ederek tasarladım. Onun için kat planlarında böyle bir durumun olmaması gerekir. 
 

Resim 3. Oda İçinde Çizilmiş Başka Bir Oda

•	Her odaya sadece bir kapı açılabileceğini kabul ettim. (Bir odadan bir ya da daha fazla odaya kapı açılabilir. Program bu durumda çalışabiliyor.)
 

Resim 4. Bir Odaya Açılan Birden Fazla Kapı

•	Lamba konumlarını odaların dışbükey olduğunu kabul ederek hesaplattığımdan doğru hesaplanmış lamba konumları için odalar dışbükey olmalı. (L tipi odalar için lamba konumları yanlış bulunuyor.

•	Aydınlatma hesabı yapılmıyor. Her odaya bir lamba yerleştiriliyor.

KULLANICI ARAYÜZÜNÜN YETERSİZLİKLERİNDEN KAYNAKLANAN KISITLAYICILAR

Kullanıcı arayüzünde yetersizlikler var. Çünkü programı geriye dönük hiçbir işlemin yapılamayacağı, sadece düşündüğüm algoritmaların uygulanışını gösterecek şekilde hazırlayabildim. Mesela:
•	Kat planı çizilirken yapılan yanlış bir işlemin geri alınmasına, duvarların konum değişikliğine, kopyalanmasına, taşınmasına hatta çizilen bir duvarın silinmesine bile imkan verilmiyor.
•	Kullanıcının tesisat planındaki eleman yerleşimine müdahalesine izin verilmiyor. Planın çizilmeden önceki lamba, anahtar, priz yerleşimini kullanıcıya onaylatma ya da değiştirerek onaylatma özelliği yok.

GİZLENMEMİŞ YA DA ENGELLENMEMİŞ DOĞAL KISITLAYICILAR

Programın kullanıcıya getirdiği kısıtlamalardan başka programın kontrolünü yapmadığı çok doğal bazı kısıtlayıcı durumların da göz önüne alınması gerekiyor. Çünkü program bu tür durumların olup olmadığını kontrol etmiyor ve anormal işlemlere izin veriyor. Sonrasında da uyguladığı algoritmalar işleyemiyor veya programın başarısız bir şekilde sonlanmasına ya da hiç sonlanamamasına sebep oluyor. Bu sebeple bu tür durumlara kullanıcının dikkat etmesi gerekiyor. Örnek olarak:
•	Birbiriyle örtüşen kapıların, pencerelerin bulunmaması gerekir.

•	Bir ucu boşta kalmış, diğer duvarları kesmeyen duvarlar olmamalı. Bu yüzden çizimlerin Snap To Grid (Giridlere kenetlenme) modunda yapılması faydalı olur.

•	Çakışık duvarlar olmamalı. (Kesişen duvarlar olabilir.)

Bu kısıtlayıcı şartları kabullenerek programı kısa zamanda tamamladım.

Programın tesisat planını çizebilmesi için kat planında yeterli ayrıntının verilmesi gerekiyor.
•	Mutlaka kat giriş kapısının olması gerekir. Çünkü dağıtım kutusunun yerini giriş kapısının konumundan bulabiliyor.
•	Kat için olduğu gibi her oda için de odaya açılan bir kapı olması gerekiyor.

PROGRAM YAZIMINDA KULLANILAN ALGORİTMA MANTIĞI

Visual C++ program geliştirme aracıyla hazırladım. 
Kat planları çizilirken beklenen genel durum duvarların bünyelerindeki yapı elemanlarıyla beraber oluşturdukları odalar dikkate alınmadan çizilmesidir. Bu sebeple AutoPlan’ın uygulayacağı algoritmaların uygulanmasına geçmeden önce bina içindeki duvarlar ait oldukları odalara göre gruplandırılmalıdır. Başka bir ifadeyle duvarlardan oluşan kat planının duvarlardan oluşan odalar ve odalardan oluşan kat planı haline dönüştürülmesi gerekir.
Örneğin Şekil 9’daki gibi çizilen bir kat planı için R1 odasının duvarları = {(1-2), (2-7), (7-6), (6-5), (5-1)} şeklinde bir gruplandırma yapılmalıdır.
 
Şekil 9 Odalar ve duvarları.
Bu işlemden sonra her odanın ayrı ayrı köşe noktalarının koordinatlarından faydalanarak köşe noktalarının ağırlık merkezi bulunur. 
Böylece lamba koordinatları bulunmuş olur.

Sonra her oda için duvarlardaki kapılara bakılır. Kapıların yönlerine bakılır. Yönü odanın içerisine olan kapı hangisiyse o kapının açıklığından duvar doğrultusunda 40 cm ilerlenir. Bulunan nokta başka bir kapı ya pencereye dek gelmiyorsa o nokta anahtar noktası olarak bulunmuş olur. Eğer o nokta bir kapı ya da pencereye dek geliyorsa o odadaki bir sonraki uygun yer hangi kapı ya da pencereye dek gelmişse o duvar elemanının 40 cm ötesi olarak belirlenir. Aynı şekilde bu noktada uygunluk testine tabi tutulur. Uygun nokta bulununcaya kadar bu işleme devam edilir ve anahtar noktası bulunmuş olur.

Anahtarın bulunmasında olduğu gibi anahtarında 40 cm ilerisinde priz yeri aranır. Aynı yöntem ile priz noktası bulunur.

Bulunan anahtar noktasıyla kuş bakışı aynı nokta buvat konumu olarak belirlenir.

Anahtar ve prizler duvarın üstü yerine duvara göre 50 cm daha oda içinde çizilir.
Anahtar ve  prizler her oda için bulunan buat ile birleştirilir.

Hangi odaya dışardan kapı ile giriş varsa o odada anahtarda olduğu gibi kapı açıklığından 1.5 m. uzakta dağıtım kutusu yeri aranır.
Düğüm noktaları duvarların köşeleri ve bağlantıları da duvarlar olacak şekilde temsil edilen bir grafik yapısı üzerinde uygulanan en kısa yol algoritmaları ile bütün buatlardan dağıtım noktası çizilecek bağlantıların köşe noktaları bulunmuş olur. Bu köşe noktaları da birleştirilerek aydınlatma projesi çizilmiş olur.

<iframe width="854" height="480" src="https://www.youtube.com/embed/WEyX45LyH0E" frameborder="0" allowfullscreen></iframe>

<iframe width="854" height="480" src="https://www.youtube.com/embed/UbL-ePjWcho" frameborder="0" allowfullscreen></iframe>
