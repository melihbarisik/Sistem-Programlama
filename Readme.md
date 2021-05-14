# 2020-2021 Sistem Programlama Ödevi
2020-2021 Sakarya Üniversitesi Bahar Dönemi Sistem Programlama Ödevidir.

## Installation
Git ile programı indirip kullanabilirsiniz [git](https://git-scm.com/)
'''bash
git clone https://github.com/melihbarisik/Sistem-Programlama.git
'''

## Usage
Programda kullanilan libfdr kutuphanesi ayri bir dosyada bulunmaktadir.
Programı calistirmak icin mf1.c dosyasinin bulunduğu dizinde make yazilmalidir.
Make sonucu program isimli bir binary dosya elde edilecek. 
Programi calistirmadan once dizinde uygun bir .kilit doyasi oldugundan emin olunmalidir. 
Program formati ./program -e/d girisDosyasi cikisDosyasi seklindedir. Oncelikle yapilacak islemi temsil eden harf parametre olarak yazilmalidir. 
Daha sonra sirasi ile giris ve cikis dosyalarinin adlari verilmelidir. 
Uygun olmayan giris sekilleri, var olmayan dosya giris denemeleri programin nerede hata yaptiginizla ilgili mesaj yazdirip   kapanmasi ile sonuclanacaktir.

'''bash
./kripto -e file encrypted #şifreleme işlemi
./kripto -d file decrypted #şifre çözme işlemi
'''

## Authors
Emre Akcan, Melih Ensar Barışık, Ömer Can Çalışır, Emine Karakayalı

## License
This program is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.
  
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.  

You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA  

## Special Thanks
Jim S. Plank's libfdr library was used in this program.
