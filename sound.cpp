#include "sound.h"

#include <QAudioFormat>
#include <QAudioOutput>
#include <QDebug>

Sound *Sound::playerHurt = new Sound(":/playerhurt.wav");
Sound *Sound::playerDeath = new Sound(":/death.wav");
Sound *Sound::monsterHurt = new Sound(":/monsterhurt.wav");
Sound *Sound::test = new Sound(":/test.wav");
Sound *Sound::pickup = new Sound(":/pickup.wav");
Sound *Sound::bossdeath = new Sound(":/bossdeath.wav");
Sound *Sound::craft = new Sound(":/craft.wav");

Sound::Sound(const QString &name)
{
	m_inputFile.setFileName(name);
	m_inputFile.open(QIODevice::ReadOnly);

	QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());

	m_audio = new QAudioOutput(info.preferredFormat());
	connect(m_audio, SIGNAL(stateChanged(QAudio::State)), SLOT(finishedPlaying(QAudio::State)));
}

void Sound::play()
{
	m_audio->start(&m_inputFile);
}

void Sound::finishedPlaying(QAudio::State state)
{
	m_inputFile.seek(0);
}
