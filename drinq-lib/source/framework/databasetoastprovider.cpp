#include "databasetoastprovider.h"
#include "controllers/databasecontrollerinterface.h"

#include <QDebug>
#include <QString>
#include <QRandomGenerator>

//Inspired by https://teksty.jeja.pl/266,okrzyki-pijackie-toasty.html

DatabaseToastProvider::DatabaseToastProvider(drinq::controllers::DatabaseControllerInterface& db)
    : m_db(db),
      m_toasts{"Piłka, bramka, gol",
               "Co by nam się!",
               "Pije Kuba do Jakuba",
               "Chluśniem, bo uśniem!",
               "Za drzewa, z których zrobią nasze trumny... Żeby jeszcze długo rosły",
               "No to chlup w ten głupi dziób",
               "Za matki naszych dzieci - co by były piękne",
               "Na prawą nożkę",
               "Na lewą nóżkę",
               "Łykniem, bo odwykniem!",
               "Rach ciach babka w piach",
               "Moja babcia chorowała - piła wódkę - wyzdrowiała",
               "Idzie osioł przez pustynie. Idzie dzień, drugi, trzeci... "
               "Słońce praży, osła meczy pragnienie. Nagle widzi: stoją dwie wielkie beczki"
               " - jedna z woda, druga z wódka. Z której zaczął pić? "
               "Oczywiście z pierwszej! Nie bądźmy więc osłami i napijmy się wódki!",
               "Płynie przez rzekę żółw, a na jego grzbiecie zwinął się jadowity wąż. "
               "Wąż myśli: 'Ugryzę - zrzuci'. Żółw myśli: 'Zrzucę - ugryzie'."
               " Wypijmy za nierozerwalna przyjaźń, co znosi wszelkie przeciwności!",
               "Pijmy, bo szkłem przejdzie",
               "Szable w dłoń",
               "Słońce świeci, ptasze kwili... Może byśmy się napili?",
               "No to cyk (powiedział budzik do zegara)",
               "Uchyl się duszo, bo ulewa idzie",
               "Buch go w migdał, aby krzyk dał",
               "Osoba godna pije do dna",
               "Kilka drinków dziennie, to zdrowe serce i marzenia senne",
               },
      m_unusedToasts(m_toasts)
{
}

DatabaseToastProvider::~DatabaseToastProvider()
{

}

Toast* DatabaseToastProvider::randomToast()
{
    if(m_unusedToasts.isEmpty())
    {
        qDebug() << "No more toasts, resetting";
        m_unusedToasts = m_toasts;
    }

    auto index = QRandomGenerator::global()->bounded(m_unusedToasts.size());
    QString text = m_unusedToasts[index];
    m_unusedToasts.removeAt(index);

    return new Toast(text, this);
}
