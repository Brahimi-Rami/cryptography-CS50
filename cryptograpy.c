#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // الحصول على مفتاح التشفير من سطر الأوامر
    string cipher_key = argv[1];

    // الأبجدية اللاتينية المعيارية للمقارنة
    const string standard_alphabet = "abcdefghijklmnopqrstuvwxyz";
    
    // الحصول على النص المراد تشفيره/فك تشفيره
    string text = get_string("text: ");
    
    // الحصول على نوع العملية (تشفير أم فك تشفير)
    string operation = "  ";
    while (strncmp(operation, "chifr", 5) != 0 && strncmp(operation, "dechifr", 7) != 0)
    {
        operation = get_string("chifr or dechifr: ");
    }

    // متغيرات الفهرسة والعدادات
    int text_index = 0;           // الفهرس الحالي في النص
    int alphabet_index = 0;       // الفهرس في الأبجدية
    int duplicate_check_index = 0; // فهرس للتحقق من التكرار
    int comparison_offset = 1;    // الإزاحة للمقارنة مع الأحرف اللاحقة
    int key_length_counter = 0;   // عداد طول مفتاح التشفير

    // متغيرات الحالة
    bool was_uppercase = true;        // هل كان الحرف الأصلي بأحرف كبيرة
    bool is_valid_key = true;         // هل المفتاح صحيح وفريد

    // ========== التحقق من صحة مفتاح التشفير ==========
    
    // حساب طول مفتاح التشفير والتأكد من أنه 26 حرف
    while (cipher_key[key_length_counter] != '\0' && key_length_counter <= 27)
    {
        key_length_counter++;
    }

    // التحقق من أن المفتاح يحتوي على 26 حرف بالضبط
    if (key_length_counter != 26)
    {
        is_valid_key = false;
    }

    // ========== التحقق من أن المفتاح يحتوي على 26 حرف فريد ==========
    while (alphabet_index <= 25 && is_valid_key == true)
    {
        // تحويل الحرف إلى حرف صغير
        cipher_key[alphabet_index] = tolower(cipher_key[alphabet_index]);

        // التحقق من أن الحرف هو حرف أبجدي
        if (cipher_key[alphabet_index] > 'z' || cipher_key[alphabet_index] < 'a')
        {
            is_valid_key = false;
        }

        // التحقق من عدم تكرار الحرف في بقية المفتاح
        while (is_valid_key == true && comparison_offset <= 25 - alphabet_index)
        {
            cipher_key[comparison_offset + alphabet_index] = tolower(cipher_key[comparison_offset + alphabet_index]);

            // إذا وجدنا حرف مكرر فالمفتاح غير صحيح
            if (cipher_key[alphabet_index] == cipher_key[comparison_offset + alphabet_index] && alphabet_index != 25)
            {
                is_valid_key = false;
            }
            comparison_offset++;
        }
        comparison_offset = 1;
        alphabet_index++;
    }

    // ========== تطبيق التشفير أو فك التشفير ==========
    if (is_valid_key == true)
    {
        // المتغير للبحث عن موقع الحرف في الأبجدية
        int alphabet_position = 0;

        // معالجة كل حرف في النص
        while (text[text_index] != '\0')
        {
            alphabet_position = 0;

            // التحقق من أن الحرف حرف كبير وحفظ هذه الحالة
            if (text[text_index] >= 'A' && text[text_index] <= 'Z')
            {
                text[text_index] = tolower(text[text_index]);
                was_uppercase = false;
            }

            // معالجة الأحرف الأبجدية فقط
            if (text[text_index] >= 'a' && text[text_index] <= 'z')
            {
                // تشفير: استبدال الحرف بما يقابله في مفتاح التشفير
                if (strncmp(operation, "chifr", 5) == 0)
                {
                    // البحث عن موقع الحرف في الأبجدية المعيارية
                    while (alphabet_position <= 25 && text[text_index] != standard_alphabet[alphabet_position])
                    {
                        alphabet_position++;
                    }

                    // استبدال الحرف بما يقابله في مفتاح التشفير
                    if (was_uppercase == false)
                    {
                        text[text_index] = toupper(cipher_key[alphabet_position]);
                    }
                    else
                    {
                        text[text_index] = cipher_key[alphabet_position];
                    }
                }
                // فك التشفير: البحث عن الحرف في مفتاح التشفير وإرجاع موقعه
                else
                {
                    // البحث عن موقع الحرف في مفتاح التشفير
                    while (alphabet_position <= 25 && text[text_index] != cipher_key[alphabet_position])
                    {
                        alphabet_position++;
                    }

                    // استبدال الحرف بالحرف المقابل في الأبجدية المعيارية
                    if (was_uppercase == false)
                    {
                        text[text_index] = toupper(standard_alphabet[alphabet_position]);
                    }
                    else
                    {
                        text[text_index] = standard_alphabet[alphabet_position];
                    }
                }
            }

            // إعادة تعيين العلم للحرف التالي
            was_uppercase = true;
            text_index++;
        }

        // طباعة النص المشفر/مفكوك التشفير
        printf("%s\n", text);
    }
    else
    {
        // طباعة رسالة خطأ إذا كان المفتاح غير صحيح
        printf("your code is incorrect\n");
    }

    return 0;
}