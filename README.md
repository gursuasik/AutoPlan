gursuasik-AutoPlan
==================

PROJENİN ÇALIŞMASI HAKKINDA GENEL BİLGİLER

Bu projede kat planı çizilen binanın, elektrik tesisat planını otomatik olarak çizebilecek bir yazılım geliştirmeye çalıştım. Böyle bir program kullanıcılara rahatlık sağlar ve önemli oranda zaman kazandırabilir.

Bu programın çalışabilmesi kat planından çıkarabileceği ipuçlarıyla mümkün olabilir. Kat planları aydınlatma projeleri için önemli ayrıntılara sahip olabiliyor. Örnek olarak:
•	Bu kat planında odalara yerleştirilecek lambalar zaten odaların orta noktalarına yerleştirilecektir.
•	Bu lambalar için kullanılacak anahtarların oda girişlerine yakın noktalara ve kapılar açıldığında kapıların arakasında kalmayacak şekilde (kapı açıklığından 40 cm mesafede) yerleşmesi gerektiğinden kat planı anahtar konumları bilgilerini de verir. 
•	Prizler de anahtarlar için konabilecek yerler de dahil oda duvarlarının uygun değişik noktalarına hazırlanan program tarafından konabilir.
 

Resim 1. Örnek Kat Planı








Bu kurallar ışığında bu kat planı üzerinde çizilebilecek aydınlatma tesisatı şu şekilde çizilir.
 

Resim 2. Kat Planı Üzerinde Çizilmiş Aydınlatma Projesi

•	Kat planlarında banyo ve tuvalet gibi bölmeler de belirtildiğinden program tarafından elde edilen bu bilgiler sayesinde buralara yerleştirilecek lamba ve prizlerin farkı yine program tarafından çizilen aydınlatma projesinde belirtilebilir.
•	Kat planlarında mutfak tezgahı, banyo küveti, lavabo gibi gösterilen ayrıntılarla beraber programın nerelere priz koyması ya da kesinlikle koymaması gerektiği bilgisi program tarafından kat planından elde edilebilir. Böylece programın aydınlatma projesine katkısı daha da fazla olabilir.

Zamanın kısıtlı olması sebebiyle; diğer ürünler yanında tercih edilebilecek ve rahat kullanılabilecek bir ürün hazırlayamasam da, böyle bir programın geliştirilebilmesine yönelik fikirlerimin uygulanabilirliğini gösteren bir program hazırladım.

Kat Planı verildiğinde Aydınlatma projesini otomatik olarak çizdiğinden programa AutoPlan adını verdim.
Program Windows XP ve üzeri işletim sistemlerinde çalışabiliyor.
Kat planlarının yine bu program arayüzünde çizilmesi gerekiyor.
Duvar, kapı, pencere ve kolon çizimine izin veriliyor.
Merdiven, mutfak, banyo tuvalet ve balkon ayrımına şimdilik izin vermiyor. Fakat programa yapılacak ilavelerle aynı algoritmalar temel alınarak bu ayrıma göre planın çizilmesi sağlanabilir.
Program çok katlı binaların çizimine imkan verebiliyor.

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

 

Resim 5. Dış Bükey Olmayan Oda (Örnek : L Tipi)

•	Aydınlatma hesabı yapılmıyor. Her odaya bir lamba yerleştiriliyor.
