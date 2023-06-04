MAX_KEY_LENGTH_GUESS = 8
alphabet = 'abcdefghijklmnopqrstuvwxyz'

# Array containing the relative frequency of each letter in the English language
english_frequences = [0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015,
                      0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749,
                      0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758,
                      0.00978, 0.02360, 0.00150, 0.01974, 0.00074]

# Returns the Index of Councidence for the "section" of ciphertext given

letter_to_ind = dict(zip(alphabet, range(len(alphabet))))
index_to_let = dict(zip(range(len(alphabet)), alphabet))

def get_ind(cipher_text):

    N = float(len(cipher_text))
    freq_sum = 0.0

    # Using Index of Coincidence formula
    for letter in alphabet:
        freq_sum += cipher_text.count(letter) * \
            (cipher_text.count(letter)-1)

    # Using Index of Coincidence formula
    ic = freq_sum/(N*(N-1))
    return ic

# Returns the key length with the highest average Index of Coincidence


def get_key_length(cipher_text):
    ic_table = []

    # Splits the ciphertext into sequences based on the guessed key length from 0 until the max key length guess (20)
    # Ex. guessing a key length of 2 splits the "12345678" into "1357" and "2468"
    # This procedure of breaking ciphertext into sequences and sorting it by the Index of Coincidence
    # The guessed key length with the highest IC is the most porbable key length
    for guess_len in range(MAX_KEY_LENGTH_GUESS):
        ic_sum = 0.0
        avg_ic = 0.0
        for i in range(guess_len):
            sequence = ""
            # breaks the ciphertext into sequences
            for j in range(0, len(cipher_text[i:]), guess_len):
                sequence += cipher_text[i+j]
            ic_sum += get_ind(sequence)
        # obviously don't want to divide by zero
        if not guess_len == 0:
            avg_ic = ic_sum/guess_len
        ic_table.append(avg_ic)

    # returns the index of the highest Index of Coincidence (most probable key length)
    first_guess = ic_table.index(sorted(ic_table, reverse=True)[0])
    second_guess = ic_table.index(sorted(ic_table, reverse=True)[1])

    # Since this program can sometimes think that a key is literally twice itself, or three times itself,
    # it's best to return the smaller amount.
    # Ex. the actual key is "dog", but the program thinks the key is "dogdog" or "dogdogdog"
    # (The reason for this error is that the frequency distribution for the key "dog" vs "dogdog" would be nearly identical)
    if first_guess % second_guess == 0:
        return second_guess
    else:
        return first_guess

# Performs frequency analysis on the "sequence" of the ciphertext to return the letter for that part of the key
# Uses the Chi-Squared Statistic to measure how similar two probability distributions are.
# (The two being the ciphertext and regular english distribution)


def freq_analysis(sequence):
    all_chi_squareds = [0] * 26

    for i in range(26):

        chi_squared_sum = 0.0

        #sequence_offset = [(((seq_ascii[j]-97-i)%26)+97) for j in range(len(seq_ascii))]
        sequence_offset = [chr(((ord(sequence[j])-97-i) % 26)+97)
                           for j in range(len(sequence))]
        v = [0] * 26
        # count the numbers of each letter in the sequence_offset already in ascii
        for l in sequence_offset:
            v[ord(l) - ord('a')] += 1
        # divide the array by the length of the sequence to get the frequency percentages
        for j in range(26):
            v[j] *= (1.0/float(len(sequence)))

        # now you can compare to the english frequencies
        for j in range(26):
            chi_squared_sum += ((v[j] - float(english_frequences[j]))
                                ** 2)/float(english_frequences[j])

        # add it to the big table of chi squareds
        all_chi_squareds[i] = chi_squared_sum

    # return the letter of the key that it needs to be shifted by
    # this is found by the smallest chi-squared statistic (smallest different between sequence distribution and
    # english distribution)
    shift = all_chi_squareds.index(min(all_chi_squareds))

    # return the letter
    return chr(shift+97)


def get_key(cipher_text, keylength):
    key = ''

    # Calculate letter frequency table for each letter of the key
    for i in range(keylength):
        sequence = ""
        # breaks the ciphertext into sequences
        for j in range(0, len(cipher_text[i:]), keylength):
            sequence += cipher_text[i+j]
        key += freq_analysis(sequence)

    return key

# Returns the plaintext given the ciphertext and a key


def decrypt(ciphertext, key):
    plain_text = ""
    split_encrypted = [
        ciphertext[i: i + len(key)] for i in range(0, len(ciphertext), len(key))
    ]

    for each_split in split_encrypted:
        i = 0
        for letter in each_split:
            number = (letter_to_ind[letter] -
                      letter_to_ind[key[i]]) % len(alphabet)
            plain_text += index_to_let[number]
            i += 1

    return plain_text


if __name__ == '__main__':

    # Filters the text so it is only alphanumeric characters, and lowercase
    ciphertext_firstversion = """"""""""""""""" Fwg atax: P’tx oh li hvabawl jwgvmjs, nw fw tfiapqz lziym,
rqgv uuwfpxj wpbk jxlnlz fptf noqe wgw.
Qoifmowl P bdg mg xv qe ntlyk ba bnjh vcf ekghn
izl fq blidb eayz jgzbwx sqwm lgglbtqgy xlip.
Pho fvvs ktf C smf ur ecul ywndxlz uv mzcz xxivw?
Qomdmowl P bgzg, oblzqdxj C swas,
B kyl btm udujs dcbfm vn yg eazl, pqzx,
oblzq Q’ow mwmzb lg ghvk gxslz, emamwx apqu, wwmazagxv nomy bhlustk.”

Ghm qvv’f nbfx h vqe vgoubdg, pgh’a nuvw shvbtmk kbvzq.
Baam jqfg pafs ixetqm wcdanw svc.
Kwn’df dixs mzy ziym llllmfa, zjid wxl
bf nom eifw hlqspuglowall, loyv sztq cu btmlw mhuq phmmla.
Kwn’df htiirk yul gx bf noqe kbls. Kwz’b agjl naz mzcuoe mekydpqzx:
lblzq’a gg moqb nhj svc, fpxjy’z va zhsx.
Uwi basn fwg’dx ouzbql rgoy tunx zyym, uv mzcz ayied wvzzmk,
qib’dq lxknywkmw an ldqzroblzq qg lbl eazev """""""""""""""""

    cipher_text = ''.join(x.lower()
                         for x in ciphertext_firstversion if x.isalpha())

    key_length = get_key_length(cipher_text)
    print("Key length is probably {}".format(key_length))
    
    key = get_key(cipher_text, key_length)
    plain_text = decrypt(cipher_text, key)

    print("Key: {}".format(key))
    print("Plaintext: {}".format(plain_text))


