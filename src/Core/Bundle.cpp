#ifdef _HEAD_BUNDLE_

template<Uint32 size>
Core::Bundle<size>::Bundle()
{
    ResetPtr();
}

template<Uint32 size>
void Core::Bundle<size>::ResetPtr()
{
    m_wptr = 0;
    m_rptr = 0;
}

template<Uint32 size>
template <typename type> void Core::Bundle<size>::Write(type& data)
{
    *(type*)(&m_data[m_wptr]) = data;
    m_wptr += sizeof(type);
}

template<Uint32 size>
template <typename type> void Core::Bundle<size>::Read(type& data)
{
    data = *(type*)(&m_data[m_rptr]);
    m_rptr += sizeof(type);
}

template<Uint32 size>
void Core::Bundle<size>::WriteStr(std::string& data)
{
    Uint32 len = data.length();
    Write<Uint32>(len);
    for(Uint32 i = 0;i < len;++i)
    {
        *(char*)(&m_data[m_wptr]) = data[i] ^ 0xCC;
        m_wptr ++;
    }
}

template<Uint32 size>
void Core::Bundle<size>::ReadStr(std::string& data)
{
    Uint32 len;
    Read<Uint32>(len);
    data.resize(len);
    for(Uint32 i = 0;i < len;++i)
    {
        data[i] = *(char*)(&m_data[m_rptr]) ^ 0xCC;
        m_rptr ++;
    }
}

template<Uint32 size>
void Core::Bundle<size>::WriteToFile(std::ofstream& out,Uint64 pos)
{
    Uint64 p = out.tellp();
    out.seekp(pos);
    out.write((char*)&m_data[0],size);
    out.seekp(p);
}

template<Uint32 size>
void Core::Bundle<size>::ReadFromFile(std::ifstream& in,Uint64 pos)
{
    Uint64 p = in.tellg();
    in.seekg(pos);
    in.read((char*)&m_data[0],size);
    in.seekg(p);
}
#endif
