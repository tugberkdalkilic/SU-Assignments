from gensim.models import Word2Vec
from gensim.models import KeyedVectors
from gensim.test.utils import common_texts
from nltk.lm import KneserNeyInterpolated
from nltk.lm.api import LanguageModel, Smoothing
from nltk.util import ngrams
from nltk.lm import MLE
from nltk.lm.preprocessing import padded_everygram_pipeline
import numpy as np
import pandas as pd
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.feature_extraction.text import CountVectorizer
import matplotlib.pyplot as plt
from wordcloud import WordCloud, STOPWORDS
import nltk
from nltk.corpus import stopwords
from nltk.tokenize import word_tokenize
from nltk.tokenize import sent_tokenize

from pandas import DataFrame

nltk.download('punkt')

nltk.download('stopwords')
stopWords = set(stopwords.words('turkish'))


stopwordstr = ["a", "acaba", "altı", "altmış", "ama", "ancak", "arada", "artık", "asla", "aslında", "ayrıca", "az", "bana", "bazen", "bazı", "bazıları", "belki",
"ben", "benden", "beni", "benim", "beri", "beş", "bile", "bilhassa", "bin", "bir", "biraz", "birçoğu", "birçok", "biri", "birisi", "birkaç", "birşey", "biz",
"bizden", "bize", "bizi", "bizim", "böyle", "böylece", "bu", "buna", "bunda", "bundan", "bunlar", "bunları", "bunların", "bunu", "bunun", "burada", "bütün", "çoğu", "çoğunu", "çok", "çünkü", "da",
"daha", "dahi", "dan", "de", "defa", "değil", "diğer", "diğeri", "diğerleri", "diye", "doksan", "dokuz", "dolayı", "dolayısıyla", "dört", "e", "edecek", "eden", "ederek", "edilecek",
"ediliyor", "edilmesi", "ediyor", "eğer", "elbette", "elli", "en", "etmesi", "etti", "ettiği", "ettiğini", "fakat", "falan", "filan", "gene", "gereği", "gerek", "gibi", "göre", "hala", "halde",
"halen", "hangi", "hangisi", "hani", "hatta", "hem", "henüz", "hep", "hepsi", "her", "herhangi", "herkes", "herkese", "herkesi", "herkesin", "hiç", "hiçbir", "hiçbiri", "i", "ı", "için",
"içinde", "iki", "ile", "ilgili", "ise", "ilgili", "işte", "itibaren", "itibariyle", "kaç", "kadar", "karşın", "kendi", "kendilerine", "kendine", "kendini", "kendisi", "kendisine", "kendisini",
"kez", "ki", "kim", "kime", "kimi", "kimin", "kimisi", "kimse", "kırk", "madem", "mi", "mı", "milyar", "milyon", "mu", "mü", "nasıl", "ne", "neden", "nedenle", "nerde", "nerede", "nereye", "neyse", "niçin", "nin", "nın", "niye", "nun", "nün", "o", "öbür", "olan", "olarak", "oldu", "olduğu",
"olduğunu", "olduklarını", "olmadı", "olmadığı", "olmak", "olması", "olmayan", "olmaz", "olsa", "olsun", "olup", "olur", "olur", "olursa", "oluyor", "on", "ön", "ona", "önce", "ondan", "onlar",
"onlara", "onlardan", "onları", "onların", "onu", "onun", "orada", "öte", "ötürü", "otuz", "öyle", "oysa", "pek", "rağmen", "sana", "sanki", "şayet", "şekilde", "sekiz", "seksen", "sen",
"senden", "seni", "senin", "şey", "şeyden", "şeye", "şeyi", "şeyler", "şimdi", "siz", "sizden", "size", "sizi", "sizin", "sonra", "şöyle", "şu", "şuna", "şunları", "şunu", "ta", "tabii", "tam",
"tamam", "tamamen", "tarafından", "trilyon", "tüm", "tümü", "u", "ü", "üç", "un", "ün", "üzere", "var", "vardı", "ve", "veya", "ya", "yani", "yapacak", "yapılan", "yapılması", "yapıyor", "yapmak",
"yaptı", "yaptığı", "yaptığını", "yaptıkları", "ye", "yedi", "yerine", "yetmiş", "yi", "yı", "yine", "yirmi", "yoksa", "yu", "yüz", "zaten", "zira"]

ngram = 3


def wordfreqs(str):

    counts = {}
    freqs = []
    ranks = []
    words = str.split()

    for word in words:
        if word in counts:
            counts[word] += 1
        else:
            counts[word] = 1
    
    values = counts.values()
    freqs = list(values)
    freqs.sort(reverse=True)
    
    for i in range(len(freqs)):
        ranks.append(i+1)

    return ranks,freqs

def listToString(l):

    str1 = ""

    for ele in l:
        str1 += ele

    return str1


def uniqcount(str):

    word_count = []
    uniques = []
    dic = {}

    words = str.split()
    
    counter = 0
    dict_size = 0

    for item in words:

        counter += 1
        
        if item in dic:
           dic[item] += 1
        else:
           dic[item] = 1
           dict_size += 1

        word_count.append(counter)
        uniques.append(dict_size)

    return uniques,word_count


def create_WordCloud(Docs, n, wordcloud_outputfile, mode, stopwords):

  if mode == "TF":

      if stopwords == True:
          tf_vectorizer = CountVectorizer(stop_words=stopwordstr)
      else:
          tf_vectorizer = CountVectorizer()

      df = DataFrame(Docs,columns=['Sentences'])
      tf_vectorizer = CountVectorizer(stop_words=stopwordstr)
      tf = tf_vectorizer.fit_transform(df)

      tf_mat = tf.toarray()
      docs = tf_mat[(tf_mat > 1).any(axis=1)]
      words = np.array(tf_vectorizer.get_feature_names())

      doc = docs[1]
      idx = (doc > 0)
      doc_words = words[idx]
      doc_counts = doc[doc > 0]

      frequencies = dict(zip(doc_words, doc_counts))

      wordcloud = WordCloud(width = n*100, height = n*100,max_words=70).fit_words(frequencies)

  elif mode == "TFIDF":
      
      if stopwords == True:
          vectorizer = TfidfVectorizer(stop_words=stopWords)
      else:
          vectorizer = TfidfVectorizer()
      X = vectorizer.fit_transform(Docs)
      df = pd.DataFrame(X.toarray(), columns = vectorizer.get_feature_names()) 
      dic_word = df.T.sum(axis=1)

      wordcloud = WordCloud(width = n*100, height = n*100, max_words=70).generate_from_frequencies(dic_word)

  plt.imshow(wordcloud, interpolation='bilinear')
  plt.axis("off")

  ##wordcloud.to_file(wordcloud_outputfile)
  plt.savefig(wordcloud_outputfile)
  plt.figure()



def create_ZiphsPlot(Docs, zips_outputfile):
    
    s = listToString(Docs)
    ranks,freqs = wordfreqs(s)

    plt.loglog(ranks, freqs, 'ro-')
    plt.xlabel('ranks', fontsize=14, fontweight='bold')
    plt.ylabel('frequencies', fontsize=14, fontweight='bold')
    plt.grid(True)
    plt.savefig(zips_outputfile)
    plt.figure()


def create_HeapsPlot(Docs, heaps_outputfile):

    s = listToString(Docs)

    x,y = uniqcount(s)

    plt.plot(y, x, 'r--')
    plt.xlabel("Number of occurrences")
    plt.ylabel("vocabulary size")
    plt.grid(True)

    plt.savefig(heaps_outputfile)
    plt.figure()

def create_LanguageModel(Docs, model_type, ngram):

    if model_type == "MLE":

        text = listToString(Docs)
        train, vocab = padded_everygram_pipeline(ngram, text)

        # Training part
        lm = MLE(ngram)

        len(lm.vocab)
        lm.fit(train, vocab)

        return lm

    elif model_type == "KneserNeyInterpolated":

        text = listToString(Docs)
        train, vocab = padded_everygram_pipeline(ngram, text)

        # Training part
        kni = KneserNeyInterpolated(ngram)

        len(kni.vocab)
        kni.fit(train, vocab)

        return kni


def generate_sentence(model, text):

    perp = 100  # starting perplexity score from a bigger number of 1

    prints = " "

    for i in range(5):

        flag = True

        s = text

        while flag == True:

            for word in model.generate(75, text):

                if word != "</s>":
                    s = s + " " + word
                else:
                    flag = False

        model_train, vocab = padded_everygram_pipeline(ngram, s)

        for i, test in enumerate(model_train):
            perplexity = model.perplexity(test)

        if perplexity < perp:
            perp = perplexity
            prints = s

    return prints, perp


def create_WordVectors(Docs, num, type_model, window):

    text = listToString(Docs)
    text = text.lower()
    all_sentences = nltk.sent_tokenize(text)

    all_words = [nltk.word_tokenize(sent) for sent in all_sentences]

    for i in range(len(all_words)):
        all_words[i] = [w for w in all_words[i] if w not in stopWords]

    if type_model == "Skipgram":

        wordvec = Word2Vec(all_words, size=num, window=window, sg=1)
        wordvec.build_vocab(all_words)
        wordvec.train(all_words, total_examples=wordvec.corpus_count, epochs=wordvec.epochs)
        return wordvec

    else:
        wordvec = Word2Vec(all_words,size=num, window=window, sg=0)
        wordvec.build_vocab(all_words)
        wordvec.train(all_words, total_examples=wordvec.corpus_count, epochs=wordvec.epochs)
        return wordvec


def use_WordRelationship(WE, example_tuple_list, example_tuple_test):

    v1 = []
    counter = 0
    tuplecount = -1

    word_vectors = WE.wv
    word_vectors.save("word2vec.wordvectors")

    wv = KeyedVectors.load("word2vec.wordvectors", mmap='r')

    for x in example_tuple_list:

        tuplecount += 1

        try:
            if v1 == []:
                v1 = wv[x[0]] - wv[x[1]]
            else:
                v1 += wv[x[0]] - wv[x[1]]
            counter += 1

        except:
            pass

    if counter == 0:
        print('Sorry, this operation cannot be performed!')

    else:
        avg_score = v1 / counter

        diff = wv[x[0]] - avg_score
        return WE.similar_by_vector(diff, topn=5)