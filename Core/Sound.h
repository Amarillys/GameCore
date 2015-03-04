#ifndef _HEAD_SOUND_
#define _HEAD_SOUND_

#include "SDLbase.h"
#include <map>
#include "FileSystem.h"

/* ������ ��һ�����������һ��ͨ��������ͬʱ���š� */
namespace Core{

    class Sound
    {
    private:
        Core::ResFile m_file;
        static unsigned int m_channelCount;
    protected:
        int m_channel;
        Mix_Chunk* m_pCnk;
        void Free();
    public:
        Sound();
        ~Sound();
        static void Init();	//��ʼ����Ƶϵͳ
        static void Quit();	//������Ƶϵͳ
        bool Load(const std::string&);	//��������
        void Play(const int _fadetime = 0);	//������������ѭ�����ɶ�ѭ����ʼ�㣬�ɵ�������
        void Play_Loop(const int _fadetime = 0);	//��ѭ����ѭ������
        void Pause();
        void Resume();
        void Stop(const int _fadetime = 0);
        void Volume(const int _vol);	//����
        bool Playing(); //�Ƿ����ڲ���
    };

    void Sound_CallBack(const int channel);
    class Sound_Loop:public Sound	//��ѭ����ѭ�������࣬�������ļ���ɣ�ͷ�����ֺ�ѭ����������
    {
    friend void Core::Sound_CallBack(const int channel);
    private:
        Mix_Chunk* m_pCnk_loop;
        Core::ResFile m_loopFile;
        static std::map<int,Mix_Chunk*> m_ChnToCnk;	//Ƶ����ѭ���ļ���ϵ
    protected:
        void Free();
    public:
        Sound_Loop();
        ~Sound_Loop();
        bool Load(const std::string&,const std::string&);
        void Play(const int _fadetime = 0);
        void Play_Loop(const int _fadetime = 0);
        void Stop(const int _fadetime = 0);
    };

}

#endif // _HEAD_SOUND_
