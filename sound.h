#ifndef SOUND_H
#define SOUND_H

#include <QAudio>
#include <QFile>

class QAudioOutput;

class Sound: public QObject
{
	Q_OBJECT

	public:
		static Sound *playerHurt;
		static Sound *playerDeath;
		static Sound *monsterHurt;
		static Sound *test;
		static Sound *pickup;
		static Sound *bossdeath;
		static Sound *craft;


	public:
		Sound(const QString &name);

		void play();

	private slots:
		void finishedPlaying(QAudio::State state);

	private:
		QFile m_inputFile;
		QAudioOutput* m_audio;
};

#endif
