Данная программа считывает текстовый файл, в каждой строчке которого указан путь к папке или файлу.
Если в строке описывается файл, то через пробел указан размер файла в байтах.
Пример входных данных:
 
TEST1\TEST\b 77
TEST1\TEST\C
TEST1\TEST\Z\test 111
TEST1\ABC\EFG\ZZZ\QWERTY\ASD\F\a.txt 16
TEST1\ABC\EFG\ZZZ\QWERTY\ASD\F\c.txt 32
TEST1\ABC\EFG\ZZZ\QWERTY\ASD\F\b.txt 32
TEST1\ABC\EFG\ZZZ\QWERTY\ASD\F\F
TEST2\TEST\Z\B
TEST2\TEST\Z\AAA\test 111
TEST2\TEST\Z\ZZZ\test 111
TEST2\TEST\Z\A
TEST2\TEST\Z\E
TEST3\TEST\B\XXX
TEST3\TEST\a 111
TEST4\ABC\EFG\ZZZ\QWERTY\ASD\F
TEST4\ABC\EFG\ZZZ\QWERTY\ASD\F2
TEST4\ABC\EFG\ZZZ\QWERTY\ASD\F3
TEST4\ABC\EFG\ZZ1
TEST4\ABC\EFG\ZZZ
TEST4\ABC\ZZZ
TEST4\ABC\EFG
 
В новый текстовый файл выводится дерево папок и файлов в таком формате:
 
TEST1
 ABC
  EFG
   ZZZ
    QWERTY
     ASD
      F
       F
       b.txt
       c.txt
       a.txt
 TEST
  C
  Z
   test
  b
TEST2
 TEST
  Z
   A
   AAA
    test
   B
   E
   ZZZ
    test
TEST3
 TEST
  B
   XXX
  a
TEST4
 ABC
  EFG
   ZZ1
   ZZZ
    QWERTY
     ASD
      F
      F2
      F3
  ZZZ
 
Внутри папки в первую очередь выводится подпапки в алфавитном порядке, затем - файлы в порядке убывания размера.
Файлы одинакового размера сортируются по алфавиту.
