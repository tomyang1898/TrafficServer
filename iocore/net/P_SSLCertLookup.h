/** @file

  A brief file description

  @section license License

  Licensed to the Apache Software Foundation (ASF) under one
  or more contributor license agreements.  See the NOTICE file
  distributed with this work for additional information
  regarding copyright ownership.  The ASF licenses this file
  to you under the Apache License, Version 2.0 (the
  "License"); you may not use this file except in compliance
  with the License.  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
 */

#ifndef _ssl_Cert_Lookup_h_
#define _ssl_Cert_Lookup_h_
#include "libts.h"
#include "P_SSLNetProcessor.h"
#include "ProxyConfig.h"

class SSLContextStorage;

class SSLCertLookup : public ConfigInfo
{
  const char *extractIPAndCert(
    matcher_line * line_info, char **addr, char **cert, char **ca, char **priKey) const;
  bool addInfoToHash(
      const SSLConfigParams * param,
      const char *strAddr, const char *cert, const char *ca, const char *serverPrivateKey);

  SSLContextStorage * ssl_storage;
  SSL_CTX * ssl_default;

  static int id;

public:
  bool buildTable(const SSLConfigParams * param);
  void checkDefaultContext();

  SSL_CTX *findInfoInHash(const char * address) const;

  // Return the last-resort default TLS context if there is no name or address match.
  SSL_CTX *defaultContext() const { return ssl_default; }

  SSLCertLookup();
  ~SSLCertLookup();

  static void startup();
  static void reconfigure();
  static SSLCertLookup * acquire();
  static void release(SSLCertLookup *p);
};

#endif
