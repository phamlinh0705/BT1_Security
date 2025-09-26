# BT1_Security
1. Caesar Cipher (Mã Caesar)

Tên gọi: Caesar cipher (mã của Julius Caesar)
Ý tưởng: dịch từng chữ cái theo một số vị trí cố định mod 26.

Thuật toán mã hóa:

Với key k (0..25).

Với mỗi chữ cái c (A..Z): E(c) = (c - 'A' + k) mod 26 + 'A'.

Bảo toàn chữ hoa/chữ thường; ký tự không chữ cái giữ nguyên (tùy chọn).

Thuật toán giải mã:

D(c) = (c - 'A' - k + 26) mod 26 + 'A'.

Không gian khóa: 26 (thực tế 25 vì k=0 là không mã hóa).

Cách phá (không cần khóa):

Brute-force thử 25 khóa; chọn bản rõ hợp lý bằng nhận diện ngôn ngữ (đếm từ phổ biến như "the", "và", vv).

Phân tích tần suất đơn giản có thể giúp (so sánh tần suất các chữ cái với tần suất chuẩn).

Mã hoá:

<img width="841" height="642" alt="image" src="https://github.com/user-attachments/assets/e57949a5-f443-468b-ae21-b9993ec4d94e" />

Giải mã:

<img width="843" height="621" alt="image" src="https://github.com/user-attachments/assets/16bd57a5-6c2b-4b26-93f8-d8afaa6fba3e" />

C++:

Mã Hoá:

<img width="349" height="383" alt="image" src="https://github.com/user-attachments/assets/0dce46ac-56e1-4217-a0e3-3080ae42585e" />

Giải mã:

<img width="353" height="335" alt="image" src="https://github.com/user-attachments/assets/c8b7bbc8-e3f2-4cea-aa4d-431a963ad394" />

2. Affine Cipher

Tên gọi: Affine cipher

Ý tưởng: kết hợp phép nhân và phép cộng trong modulo 26: E(x) = (a*x + b) mod 26, với x = chỉ số chữ cái.

Yêu cầu khóa: a và 26 phải nguyên tố cùng nhau (gcd(a,26)=1), và b là số trong 0..25.

Thuật toán mã hóa:

E(x) = (a*x + b) mod 26.

Thuật toán giải mã:

Tìm nghịch đảo modulo a_inv của a (a * a_inv ≡ 1 (mod 26)).

D(y) = a_inv * (y - b) mod 26.

Không gian khóa: số cặp (a,b) với gcd(a,26)=1 và b∈[0,25]. Các a hợp lệ (mod26) = 12 giá trị (1,3,5,7,9,11,15,17,19,21,23,25) → 12*26 = 312 khóa.

Cách phá (không cần khóa):

Brute-force 312 khả năng; dùng phân tích tần suất để chọn bản rõ hợp lý.

Nếu có một chữ cái biết trước (known-plaintext) thì có thể giải hệ 2 phương trình để tìm a,b.

Mã hoá:

<img width="851" height="618" alt="image" src="https://github.com/user-attachments/assets/94483960-cdab-4fc5-9799-9ebec039a9a2" />

Giãi mã:

<img width="847" height="629" alt="image" src="https://github.com/user-attachments/assets/ed196504-922d-4f6d-bbc6-9bbd090f0ab1" />

C++:

Mã hoá:

<img width="337" height="347" alt="image" src="https://github.com/user-attachments/assets/04425056-4ea3-4a15-84d4-fc13f778ddb6" />

Giải mã:

<img width="399" height="357" alt="image" src="https://github.com/user-attachments/assets/b8a35c8f-b850-47c4-aa17-c701899013b8" />

3. Hoán vị (Permutation / Transposition Cipher)

Tên gọi: Transposition cipher (Mã hoán vị) — có nhiều biến thể: columnar transposition (hoán vị theo cột), rail fence, v.v. Ở đây mô tả Columnar Transposition (hàng -> cột).

Ý tưởng: viết bản rõ xuống hàng theo số cột = key length, sau đó đọc cột theo thứ tự hoán vị của khóa (ví dụ khóa "4312" hoặc dùng chữ cái của khóa để sắp cột theo chữ cái).

Thuật toán mã hóa (columnar):

Chọn khóa: một chuỗi ký tự (ví dụ "ZEBRAS") — ta gán thứ tự số cho mỗi ký tự theo thứ tự chữ cái nhỏ->lớn (tạo hoán vị).

Viết bản rõ theo hàng vào lưới có n cột. Nếu thiếu ô, padding ký tự (ví dụ 'X').

Đọc cột theo thứ tự khóa đã sắp xếp, nối thành bản mã.

Thuật toán giải mã:

Biết số cột và thứ tự đọc cột, ta phân chia bản mã thành các cột tương ứng, điền cột theo thứ tự, rồi đọc theo hàng.

Không gian khóa: phụ thuộc vào độ dài khóa n: số hoán vị = n! (rất lớn khi n tăng).

Cách phá (không cần khóa):

Brute-force với các hoán vị nhỏ.

Dùng phân tích mô típ (pattern), trắc nghiệm độ hợp lý của kết quả (ngôn ngữ).

Kết hợp tấn công known-plaintext hoặc dùng heuristics + simulated annealing để tìm hoán vị tối ưu (dùng scoring function ngôn ngữ).

Mã Hoá:

<img width="861" height="636" alt="image" src="https://github.com/user-attachments/assets/a0a4ee90-da6b-4b4f-8630-f8a8abfc30de" />

Giải Mã:

<img width="834" height="619" alt="image" src="https://github.com/user-attachments/assets/2ec30daf-214d-44ef-af84-420487a8d6cc" />

C++:

Mã Hoá:

<img width="465" height="430" alt="image" src="https://github.com/user-attachments/assets/a7491a8c-dfed-40ff-9ff0-548f27042de6" />

Giải Mã:

v<img width="404" height="434" alt="image" src="https://github.com/user-attachments/assets/4b5b4435-9662-4dfb-a8dd-e1ac90ee1d47" />

4. Vigenère Cipher

Tên gọi: Vigenère cipher

Ý tưởng: một dạng Caesar nhưng key là chuỗi; dùng phép cộng modulo 26 với mỗi chữ cái key lặp lại (polyalphabetic).

Thuật toán mã hóa:

Key: K = k0 k1 ... km-1 (chữ cái).

Bản rõ P = p0 p1 ... pn-1.

E(pi) = (pi + k_{i mod m}) mod 26.

Thuật toán giải mã:

D(ci) = (ci - k_{i mod m} + 26) mod 26.

Không gian khóa: độ dài key * 26^m (rất lớn nếu key dài). Nếu giới hạn key chữ cái độ dài m: 26^m.

Cách phá (không cần khóa):

Kasiski examination: tìm các lặp đoạn trong bản mã để ước tính độ dài key (khoảng cách các lặp có chung ước).

Sau khi ước độ dài m, tách bản mã thành m stream và dùng phân tích tần suất (mỗi stream là Caesar) để tìm shift cho từng stream.

Index of Coincidence (IC) cũng dùng để ước độ dài key.

Mã Hoá:

<img width="835" height="622" alt="image" src="https://github.com/user-attachments/assets/e1ad020e-4ac9-41d9-a4ef-84b6365e07d2" />

Giải Mã:

<img width="853" height="600" alt="image" src="https://github.com/user-attachments/assets/77f70c94-21f2-45ac-9c5c-827a9e9c1994" />

C++:

Mã Hoá :

<img width="407" height="331" alt="image" src="https://github.com/user-attachments/assets/86f35e5e-e526-447e-976a-be893cd65864" />

Giải Mã:

<img width="369" height="344" alt="image" src="https://github.com/user-attachments/assets/990865a4-dd16-4190-a35d-88be8bb630a5" />

5. Playfair Cipher

Tên gọi: Playfair cipher (cổ, do Charles Wheatstone phổ biến bởi Lord Playfair)

Ý tưởng: dùng bảng 5x5 (kết hợp I/J hoặc loại bỏ Q tùy biến) và mã hai chữ 1 lần (digraphs). Playfair là cipher thay thế cặp chữ.

Thiết lập bảng (5x5):

Key: ví dụ "MONARCHY" — loại bỏ ký tự trùng, ghi key vào matrix left->right top->down, sau đó điền các chữ cái còn lại (thường hợp nhất I/J thành một ô).

Tiền xử lý bản rõ:

Thay I/J (thống nhất), loại bỏ ký tự không chữ.

Tách bản rõ thành digraphs (cặp). Nếu hai chữ trong một cặp giống nhau, chèn một ký tự filler (thường 'X') giữa để tránh cặp giống (ví dụ "BALLOON" -> BA LX LO ON -> BA LX LO ON X). Nếu cuối cùng còn lẻ, thêm filler.

Thuật toán mã hóa cho mỗi digraph (a,b):

Nếu a và b cùng hàng: thay mỗi chữ bằng chữ bên phải nó (vòng vòng).

Nếu cùng cột: thay bằng chữ bên dưới nó (vòng vòng).

Nếu không cùng hàng và cột: thay bắng chữ ở cùng hàng của a nhưng cột của b (hình chữ nhật) — (a_row, b_col) và (b_row, a_col).

Giải mã:

Tương tự nhưng dùng trái/trên thay vì phải/dưới.

Không gian khóa: permutation của 25 ký tự ~ 25! rất lớn.

Cách phá (không cần khóa):

Phân tích digraph frequencies; tấn công brute-force rất khó; tấn công dựa trên Hill-climbing / simulated annealing + scoring ngôn ngữ thường áp dụng.

Mã Hoá:

<img width="870" height="623" alt="image" src="https://github.com/user-attachments/assets/ed30a776-063e-4ecc-a300-f67e10a9382f" />

Giải Mã:

<img width="840" height="630" alt="image" src="https://github.com/user-attachments/assets/86680543-35c2-4910-a457-c4796df84087" />

C++:

Mã Hoá:

<img width="421" height="439" alt="image" src="https://github.com/user-attachments/assets/f2e1c7e0-eb5a-48f6-b146-e9a2f1ccaeef" />

Giải Mã:

<img width="393" height="345" alt="image" src="https://github.com/user-attachments/assets/f72dc067-cf68-48f5-bc46-2c6dda025d01" />
