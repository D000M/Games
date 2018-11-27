/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: default
 *
 * Created on November 7, 2018, 11:37 AM
 */

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <algorithm>

#include "lecture1/CeaserCipher.h"
#include "lecture1/CeaserDecrypthor.h"
#include "lecture1/ViginerCipher.h"
#include "lecture1/ViginerDecryptor.h"

using namespace std;

/*
 * 
 */

void testCeaserEncrypt() {
    CeaserCipher text("files/TextToEncrypt.txt", 5);
    text.encryptFile();
    text.saveResult("files/EncryptedText5.txt");
}

void testCeaserDecryptor() {
    CeaserDecrypthor decrypt("files/EncryptedText5.txt", 5);
    decrypt.decrypt();
    decrypt.saveDecrypredFile("files/DecryptedText5.txt");
}

void testViginerCipher() {
    ViginerCipher vs{"files/vsTextToEncrypt.txt", "crypto"};
    vs.encrypt();
    vs.saveEncryptedFile("files/vsEncryptefFile.txt");
}

void testViginerDecryptor() {
    ViginerDecryptor vd{"files/vsEncryptefFile.txt", "crypto"};
    vd.decrypt();
    vd.saveDecrypted("files/vsDecryptedFile.txt");
}

int encodeIn8Bit(char c);

int convertTo8Base(int n) {
    std::string result = "";
    stringstream ss;

    while(n > 0) {
        int reminder = n % 8;
        ss << reminder;
        n /= 8;
    }
    result = ss.str();
    std::reverse(result.begin(), result.end());
    
    return atoi(result.c_str());
    
}

void convertOctToHex(int n) {
    std::string result = "";
    stringstream ss;
    ss << std::hex << n;
    result = ss.str();
    std::cout << result;
}

void printString(const std::string& text) {

    for(int i = 0; i < text.length(); i++) {
        convertOctToHex(convertTo8Base(encodeIn8Bit(text.at(i))));
    }
}

int encodeIn8Bit(char c) {
    return int(c);
}

void strXoR(const std::string& first, const std::string& second) {

    if(first.length() > second.length()) {
        for(int i = 0; i < second.length(); i++) {
            char a;
            if(i < second.length()) {
                a = second.at(i) ^ first.at(i);
            }
            char tc = (a + 26);
            if(tc >= 'a' && tc <= 'z') {
                std::cout << tc;
            }
            else {
                std::cout << '_';
            }
        }
    }
    else {
        for(int i = 0; i < first.length(); i++) {
            char a;
            if(i < first.length()) {
                a = second.at(i) ^ first.at(i);
            }
            char tc = (a + 26);
            if(tc >= 'a' && tc <= 'z') {
                std::cout << tc;
            }
            else {
                std::cout << '_';
            }
        }
    }
}

void printSomething() {
    char c = ' ';
    char temp = ' ';
    for(int i = 'A'; i < 'Z'; i++) {
        temp = i ^ c;
        std::cout << temp << " ";
    }
    std::cout << std::endl;
    for(int i = 'a'; i < 'z'; i++) {
        temp = i ^ c;
        std::cout << temp << " ";
    }
}

void compareStrings(const std::string& first, const std::string& second) {
    std::string result = "";
    if(first.length() > second.length()) {
        for(int i = 0; i < second.length(); i++) {
            if(first.at(i) == '_' && second.at(i) == '_') {
                result += '_';
            }
            else if(first.at(i) != '_' && second.at(i) == '_') {
                result += ' ';
            }
            else if(first.at(i) != '_' && second.at(i) != '_') {
                result += 's';
            }
            else {
                result += '_';
            }
        }
    }
    else {
        for(int i = 0; i < first.length(); i++) {
            if(first.at(i) == '_' && second.at(i) == '_') {
                result += '_';
            }
            else if(first.at(i) != '_' && second.at(i) == '_') {
                result += ' ';
            }
            else if(first.at(i) != '_' && second.at(i) != '_') {
                result += 's';
            }
            else {
                result += '_';
            }
        }
    }
    std::cout << result << std::endl;
}

int main(int argc, char** argv) {

    //Hint: XOR the ciphertexts together, and consider what happens when a space is XORed with a character in [a-zA-Z].
    std::string firstTxt =  "315c4eeaa8b5f8aaf9174145bf43e1784b8fa00dc71d885a804e5ee9fa"
        "40b16349c146fb778cdf2d3aff021dfff5b403b510d0d0455468aeb98622b137dae857553ccd88"
        "83a7bc37520e06e515d22c954eba5025b8cc57ee59418ce7dc6bc41556bdb36bbca3e8774301fb"
        "caa3b83b220809560987815f65286764703de0f3d524400a19b159610b11ef3e";
    
    std::string secondTxt = "234c02ecbbfbafa3ed18510abd11fa724fcda2018a1a8342cf064bbde5"
        "48b12b07df44ba7191d9606ef4081ffde5ad46a5069d9f7f543bedb9c861bf29c7e205132eda93"
        "82b0bc2c5c4b45f919cf3a9f1cb74151f6d551f4480c82b2cb24cc5b028aa76eb7b4ab24171ab3"
        "cdadb8356f";
    
    std::string thirdTxt = "32510ba9a7b2bba9b8005d43a304b5714cc0bb0c8a34884dd91304b8ad4"
        "0b62b07df44ba6e9d8a2368e51d04e0e7b207b70b9b8261112bacb6c866a232dfe257527dc2939"
        "8f5f3251a0d47e503c66e935de81230b59b7afb5f41afa8d661cb";
    
    std::string fourthTxt = "32510ba9aab2a8a4fd06414fb517b5605cc0aa0dc91a8908c2064ba8ad"
        "5ea06a029056f47a8ad3306ef5021eafe1ac01a81197847a5c68a1b78769a37bc8f4575432c198"
        "ccb4ef63590256e305cd3a9544ee4160ead45aef520489e7da7d835402bca670bda8eb775200b8"
        "dabbba246b130f040d8ec6447e2c767f3d30ed81ea2e4c1404e1315a1010e7229be6636aaa";
    
    std::string fifthTxt = "3f561ba9adb4b6ebec54424ba317b564418fac0dd35f8c08d31a1fe9e24"
        "fe56808c213f17c81d9607cee021dafe1e001b21ade877a5e68bea88d61b93ac5ee0d562e8e958"
        "2f5ef375f0a4ae20ed86e935de81230b59b73fb4302cd95d770c65b40aaa065f2a5e33a5a0bb5d"
        "caba43722130f042f8ec85b7c2070";
    
    std::string sixthTxt = "32510bfbacfbb9befd54415da243e1695ecabd58c519cd4bd2061bbde24"
        "eb76a19d84aba34d8de287be84d07e7e9a30ee714979c7e1123a8bd9822a33ecaf512472e8e8f8"
        "db3f9635c1949e640c621854eba0d79eccf52ff111284b4cc61d11902aebc66f2b2e436434eacc"
        "0aba938220b084800c2ca4e693522643573b2c4ce35050b0cf774201f0fe52ac9f26d71b6cf61a"
        "711cc229f77ace7aa88a2f19983122b11be87a59c355d25f8e4";
    
    std::string sevenTxt = "32510bfbacfbb9befd54415da243e1695ecabd58c519cd4bd90f1fa6ea5"
        "ba47b01c909ba7696cf606ef40c04afe1ac0aa8148dd066592ded9f8774b529c7ea125d298e888"
        "3f5e9305f4b44f915cb2bd05af51373fd9b4af511039fa2d96f83414aaaf261bda2e97b170fb5c"
        "ce2a53e675c154c0d9681596934777e2275b381ce2e40582afe67650b13e72287ff2270abcf73b"
        "b028932836fbdecfecee0a3b894473c1bbeb6b4913a536ce4f9b13f1efff71ea313c8661dd9a4c"
        "e";
    
    std::string eightTxt = "315c4eeaa8b5f8bffd11155ea506b56041c6a00c8a08854dd21a4bbde54"
        "ce56801d943ba708b8a3574f40c00fff9e00fa1439fd0654327a3bfc860b92f89ee04132ecb929"
        "8f5fd2d5e4b45e40ecc3b9d59e9417df7c95bba410e9aa2ca24c5474da2f276baa3ac325918b2d"
        "aada43d6712150441c2e04f6565517f317da9d3";
    
    std::string ninthTxt = "271946f9bbb2aeadec111841a81abc300ecaa01bd8069d5cc91005e9fe4"
        "aad6e04d513e96d99de2569bc5e50eeeca709b50a8a987f4264edb6896fb537d0a716132ddc938"
        "fb0f836480e06ed0fcd6e9759f40462f9cf57f4564186a2c1778f1543efa270bda5e933421cbe8"
        "8a4a52222190f471e9bd15f652b653b7071aec59a2705081ffe72651d08f822c9ed6d76e48b63a"
        "b15d0208573a7eef027";
    
    std::string tenthTxt = "466d06ece998b7a2fb1d464fed2ced7641ddaa3cc31c9941cf110abbf40"
        "9ed39598005b3399ccfafb61d0315fca0a314be138a9f32503bedac8067f03adbf3575c3b8edc9"
        "ba7f537530541ab0f9f3cd04ff50d66f1d559ba520e89a2cb2a83";
    
    std::string targetTxt = "32510ba9babebbbefd001547a810e67149caee11d945cd7fc81a05e9f8"
        "5aac650e9052ba6a8cd8257bf14d13e6f0a803b54fde9e77472dbff89d71b57bddef121336cb85"
        "ccb8f3315f4b52e301d16e9f52f904";
    
//    strXoR(secondTxt, thirdTxt);
    
    /*
     *1-2 _____q___t_q_x_l_w_____n_____j____u____oup_____mup_m___w_n_____k___q_______l_y_n___l_________j______wnwp_m___t____u____q___p___________________n_k_________n___m___p_______p___k___l_k_____p_q_q__t______n___t_____j_k___q___q_n

     *1-3 ___l___r_____t_r_____o___o________up_l__up_j____v__p_k_________k___q_____l__v__q_s_m_p_j_p_________lwlv______t____u__________________p_______j___m_________________s______t__p___y__s____o_m_p
     *2-3 ___l_j_t_o_j_____v___o_l_q___n_____n_j_l___o___p_y___p_v_k_______________n_ovr___w___v_l_n___p_____n___n_q_____________n___k_________m_______j_p___________j___o__________wq_j_p_x_lsn___n____      
     */
//    printSomething();
    
    std::string first =  "_____q___t_q_x_l_w_____n_____j____u____oup_____mup_m___w_n_____k___q_______l_y_n___l_________j______wnwp_m___t____u____q___p___________________n_k_________n___m___p_______p___k___l_k_____p_q_q__t______n___t_____j_k___q___q_n";
    std::string second = "___l___r_____t_r_____o___o________up_l__up_j____v__p_k_________k___q_____l__v__q_s_m_p_j_p_________lwlv______t____u__________________p_______j___m_________________s______t__p___y__s____o_m_p";
    
    compareStrings(first, second);
    
    return 0;
}

