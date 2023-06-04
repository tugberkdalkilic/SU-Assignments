import project02,sys,pickle
import matplotlib.pyplot as plt


def read_Docs(path):
    """

    This function will return a list which includes documents as string format.

    Parameters:
    path: path for the pickle file we will provide.

    """
    with open(path,'rb') as P:
        Docs = pickle.load(P)
    return Docs
    
    
if __name__ == "__main__":


    list_of_documents_path = sys.argv[1]
    Docs=read_Docs(list_of_documents_path)[:500]
    

    
    try: 
        heaps_outputfile = "outputs/project2_heaps.png"
        project02.create_HeapsPlot(Docs,heaps_outputfile)
        print("Heaps' Law function worked!")
    except: 
        print("Heaps' Law function DID NOT worked!")
    plt.clf()
    try:
        zips_outputfile = "outputs/project2_zips.png"
        project02.create_ZiphsPlot(Docs,zips_outputfile)
        print("Ziph's Law function worked!")
    except: 
        print("Ziph's Law function DID NOT worked!")
    plt.clf()    
    try:
        wordcloud_outputfile = "outputs/project2_wordcloud.png"
        project02.create_WordCloud(Docs,8,wordcloud_outputfile,mode="TFIDF",stopwords=True)
        print("WordCloud function worked!")
    except:
        print("WordCloud function DID NOT worked!")
    plt.clf()    
        
    try: 
        LM3_MLE = project02.create_LanguageModel(Docs,model_type="MLE",ngram=3)
        sentence,perplexity = project02.generate_sentence(LM3_MLE,text="milli")   
        print(sentence,perplexity)
    except: 
        print("MLE language model DID NOT worked!")
    try:
        LM3_KneserNeyInterpolated = project02.create_LanguageModel(Docs,model_type="KneserNeyInterpolated",ngram=3)
        sentence,perplexity = project02.generate_sentence(LM3_KneserNeyInterpolated,text="milli")
        print(sentence,perplexity)
    except:   
        print("KneserNey language model DID NOT worked!")
    
    try:
        WE = project02.create_WordVectors(Docs,300,'cbow',5)
    except:
        print("Word2Vec DID NOT worked!")
    example_tuple_list =[('fransa','paris'),
                      ('almanya','berlin'),
                      ('italya','roma'),
                      ('ispanya','madrid'),
                      ('hollanda','amsterdam'),
                      ('ingiltere','londra'),
                      ('türkiye','ankara')]
    example_tuple_test =('rusya','')
    
    
    try:
        project02.use_WordRelationship(WE,example_tuple_list,example_tuple_test)
    except:
        print("WordRelationships DID NOT worked!")