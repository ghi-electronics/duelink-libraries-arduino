#pragma once

#ifdef ARDUINO
#include "Arduino.h"
#endif

#include "DUELinkTransport.h"

class SystemController
{
public:
  SystemController(DUELinkTransport &transport)
  {
    m_pTransport = &transport;
  }

  float Info(int code)
  {
    char cmd[32];
    sprintf(cmd, "info(%d)", code);
    m_pTransport->WriteCommand(cmd);
    DUELinkTransport::Response result = m_pTransport->ReadResponse();
    if (result.success)
      return atof(result.response.c_str());
    return 0;
  }

  void Reset(int option)
  {
    char cmd[32];
    sprintf(cmd, "reset(%d)", option);
    m_pTransport->WriteCommand(cmd);
    if (option == 1) {
      m_pTransport->ReadResponse();
      m_pTransport->WriteCommand(cmd);
    }
    m_pTransport->Disconnect();
  }

  int GetTickMicroseconds() {
    
    m_pTransport->WriteCommand("tickus()");
    DUELinkTransport::Response result = m_pTransport->ReadResponse();

    if (result.success)
        return atoi(result.response.c_str());
    return false;
  }

  int GetTickMilliseconds() {
    
    m_pTransport->WriteCommand("tickms()");
    DUELinkTransport::Response result = m_pTransport->ReadResponse();

    if (result.success)
        return atoi(result.response.c_str());
    return false;
  }

  bool StatLed(int highPeriod, int lowPeriod, int count)
  {
    char cmd[64];
    sprintf(cmd, "statled(%d,%d,%d)", highPeriod, lowPeriod, count);
    m_pTransport->WriteCommand(cmd);

    DUELinkTransport::Response result = m_pTransport->ReadResponse();

    return result.success;
  }

  void Shutdown(int wkpin) {
    char cmd[64];
    sprintf(cmd, "shtdn(%d)", wkpin);
    m_pTransport->WriteCommand(cmd);

    // shutdown no response

  }

  // void SetArrayValue(const char *var, const void *data, int offset, int count)
  // {
    // if (strlen(var) != 2 || (var[1] < '0' && var[1] > '9'))
      // return;
    
    // char cmd[32];

    // sprintf(cmd, "dim %s[%d]",var,count);
    // DUELinkTransport::Response result = m_pTransport->WriteCommand(cmd);
    // if (!result.success) return;

    // sprintf(cmd, "strmwr(%s,%d)", var, count);
    // result = m_pTransport->WriteCommand(cmd);
    // if (!result.success) return;

    // char prefix = tolower(var[0]);
    // if (prefix == 'a')
    // {
      // m_pTransport->streamOutFloats(((const float *)data) + offset, count);
    // }
    // else if (prefix == 'b')
    // {
      // m_pTransport->streamOutBytes(((const char *)data) + offset, count);
    // }
  // }

private:
  DUELinkTransport *m_pTransport = NULL;
};
