// scripts.js

// Mã hóa Caesar
function caesarCipher(text, key, decrypt = false) {
    key = ((key % 26) + 26) % 26;
    if (decrypt) key = -key;
    return text.split('').map(c => {
        if (c >= 'A' && c <= 'Z') return String.fromCharCode((c.charCodeAt(0) - 65 + key + 26) % 26 + 65);
        if (c >= 'a' && c <= 'z') return String.fromCharCode((c.charCodeAt(0) - 97 + key + 26) % 26 + 97);
        return c;
    }).join('');
}

// Mã hóa Playfair
function playfairCipher(text, key, decrypt = false) {
    const createMatrix = (key) => {
        const alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ"; // Loại bỏ 'J'
        key = key.toUpperCase().replace(/J/g, "I").replace(/[^A-Z]/g, "");
        const uniqueKey = [...new Set(key + alphabet)];
        return Array.from({ length: 5 }, (_, i) => uniqueKey.slice(i * 5, i * 5 + 5));
    };

    const findPosition = (matrix, char) => {
        for (let row = 0; row < 5; row++) {
            for (let col = 0; col < 5; col++) {
                if (matrix[row][col] === char) return [row, col];
            }
        }
        return null;
    };

    const prepareText = (text) => {
        text = text.toUpperCase().replace(/J/g, "I").replace(/[^A-Z]/g, "");
        let prepared = "";
        for (let i = 0; i < text.length; i += 2) {
            const a = text[i];
            const b = text[i + 1] || "X";
            prepared += a + (a === b ? "X" : b);
        }
        return prepared;
    };

    const matrix = createMatrix(key);
    text = prepareText(text);

    return text.match(/.{1,2}/g).map(pair => {
        const [a, b] = pair;
        const [rowA, colA] = findPosition(matrix, a);
        const [rowB, colB] = findPosition(matrix, b);

        if (rowA === rowB) {
            // Cùng hàng
            return matrix[rowA][(colA + (decrypt ? 4 : 1)) % 5] +
                   matrix[rowB][(colB + (decrypt ? 4 : 1)) % 5];
        } else if (colA === colB) {
            // Cùng cột
            return matrix[(rowA + (decrypt ? 4 : 1)) % 5][colA] +
                   matrix[(rowB + (decrypt ? 4 : 1)) % 5][colB];
        } else {
            // Hình chữ nhật
            return matrix[rowA][colB] + matrix[rowB][colA];
        }
    }).join('');
}

// Mã hóa Affine
function affineCipher(text, a, b, decrypt = false) {
    const modInverse = (a, m) => {
        for (let x = 1; x < m; x++) if ((a * x) % m === 1) return x;
        return -1;
    };
    const aInv = decrypt ? modInverse(a, 26) : a;
    if (decrypt && aInv === -1) return "Lỗi: 'a' không nguyên tố cùng nhau với 26.";
    return text.split('').map(c => {
        if (c >= 'A' && c <= 'Z') {
            const x = c.charCodeAt(0) - 65;
            const result = decrypt ? (aInv * (x - b + 26)) % 26 : (a * x + b) % 26;
            return String.fromCharCode(result + 65);
        }
        if (c >= 'a' && c <= 'z') {
            const x = c.charCodeAt(0) - 97;
            const result = decrypt ? (aInv * (x - b + 26)) % 26 : (a * x + b) % 26;
            return String.fromCharCode(result + 97);
        }
        return c;
    }).join('');
}

// Mã hóa Hoán vị
function permutationCipher(text, key, decrypt = false) {
    const col = key.length;
    const row = Math.ceil(text.length / col);
    const matrix = Array.from({ length: row }, () => Array(col).fill('X'));
    let k = 0;

    if (!decrypt) {
        for (let i = 0; i < row && k < text.length; i++) {
            for (let j = 0; j < col && k < text.length; j++) {
                matrix[i][j] = text[k++];
            }
        }
        const order = [...key].map((c, i) => [c, i]).sort();
        return order.map(([_, idx]) => matrix.map(row => row[idx]).join('')).join('');
    } else {
        const order = [...key].map((c, i) => [c, i]).sort();
        k = 0;
        for (const [_, idx] of order) {
            for (let i = 0; i < row; i++) {
                matrix[i][idx] = text[k++];
            }
        }
        return matrix.flat().join('');
    }
}

// Mã hóa Vigenere
function vigenereCipher(text, key, decrypt = false) {
    const shift = (c, k, decrypt) => {
        const base = c >= 'a' ? 97 : 65;
        const offset = decrypt ? -k : k;
        return String.fromCharCode((c.charCodeAt(0) - base + offset + 26) % 26 + base);
    };
    key = key.toLowerCase();
    let j = 0;
    return text.split('').map(c => {
        if (/[a-zA-Z]/.test(c)) {
            const k = key[j % key.length].charCodeAt(0) - 97;
            j++;
            return shift(c, k, decrypt);
        }
        return c;
    }).join('');
}

// Hàm xử lý mã hóa
function handleEncrypt(cipher, text, key) {
    switch (cipher) {
        case "caesar":
            return caesarCipher(text, parseInt(key), false);
        case "playfair":
            return playfairCipher(text, key, false);
        case "affine":
            const [a, b] = key.split(',').map(Number);
            return affineCipher(text, a, b, false);
        case "permutation":
            return permutationCipher(text, key, false);
        case "vigenere":
            return vigenereCipher(text, key, false);
        default:
            return "Phương pháp mã hóa không hợp lệ.";
    }
}

// Hàm xử lý giải mã
function handleDecrypt(cipher, text, key) {
    switch (cipher) {
        case "caesar":
            return caesarCipher(text, parseInt(key), true);
        case "playfair":
            return playfairCipher(text, key, true);
        case "affine":
            const [a, b] = key.split(',').map(Number);
            return affineCipher(text, a, b, true);
        case "permutation":
            return permutationCipher(text, key, true);
        case "vigenere":
            return vigenereCipher(text, key, true);
        default:
            return "Phương pháp giải mã không hợp lệ.";
    }
}

// Xử lý sự kiện mã hóa
document.getElementById("encrypt").addEventListener("click", () => {
    const cipher = document.getElementById("cipher").value;
    const text = document.getElementById("inputText").value;
    const key = document.getElementById("key").value;
    const result = handleEncrypt(cipher, text, key);
    document.getElementById("outputText").value = result;
});

// Xử lý sự kiện giải mã
document.getElementById("decrypt").addEventListener("click", () => {
    const cipher = document.getElementById("cipher").value;
    const text = document.getElementById("inputText").value;
    const key = document.getElementById("key").value;
    const result = handleDecrypt(cipher, text, key);
    document.getElementById("outputText").value = result;
});