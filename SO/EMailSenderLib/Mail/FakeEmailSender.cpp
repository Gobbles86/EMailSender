#include "FakeEmailSender.h"
#include "File/FileReaderService.h"
#include "File/FlatFileReader.h"
#include "File/XMLFileReader.h"
#include "Database/DatabaseConnectionReader.h"

using namespace Mail;

void FakeEmailSender::readFile()
{
    auto flatFileReader = std::make_shared<File::FlatFileReader>();
    auto xmlFileReader = std::make_shared<File::XMLFileReader>();
    auto dbConnectionReader = std::make_shared<Database::DatabaseConnectionReader>();

    auto fileReaderService = std::make_shared<File::FileReaderService>( flatFileReader );
    fileReaderService->registerFormatReader( xmlFileReader );
    fileReaderService->registerFormatReader( dbConnectionReader );

    _messageBody = fileReaderService->getMessageBodyFromFile( getFileName() );
}

void FakeEmailSender::sendEmail()
{
    auto messageBody = getMessageBody();

    Q_UNUSED( messageBody ); // This is a fake, it won't actually send mails.

    qDebug() << "Sending message body" << messageBody;
    // In a productive class, there would be a lot of TCP and SMTP stuff here.
}