--------------------------------------------------------------------------------------------

Chương trình chưa hoàn thiện, còn nhiều lỗi tiềm ẩn, ngoại lệ, hệ thống hóa (tính sáng sủa và dễ hiểu), hiệu suất và giao diện người dùng.

--------------------------------------------------------------------------------------------

VỀ CÁC FILE

DynamicArray.h
giống như ArrayList trong Java


Node.h
Mỗi đối tượng của lớp này là một Node của một loại cây được gọi là LettersTree, cây này chứa trong file LettersTree.h
Mỗi Node chứa thông tin gồm:
+ Một chữ cái
+ Một mảng các con trỏ Node* trỏ đến chữ cái tiếp theo
+ makeSense là true nếu từ Node tổ tiên lớn nhất đến nó tạo thành một dãy chữ cái có nghĩa


LettersTree.h
Là một cây, tác dụng chính chỉ là cung cấp tính năng gợi ý từ


EngVieDict.h
chứa:
+ lớp phụ Vocab, lớp Vocab này chính là chỉ chứa từ vựng và nghĩa của nó và một số tính năng phụ trợ thêm
+ Một DynamicArray chứa các con trỏ Vocab*, đóng vai trò như là bảng băm để truy cập từ vựng nhanh hơn
+ Một đối tượng LettersTree chứa lượng từ vựng bằng với bảng băm chứa, mục đích chính của nó là cung cấp tính năng gợi ý từ cho từ điển


WordGame.h
kế thừa từ điển và thêm các trò chơi, chủ yếu chơi trên file từ vựng mà người dùng thêm vào (PracticeList.txt)




