/*
 *
 * Copyright 2014, Google Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */


#include <grpc/grpc_security.h>

#include <grpc++/server_credentials.h>

namespace grpc {

ServerCredentials::ServerCredentials(grpc_server_credentials* c_creds)
    : creds_(c_creds) {}

ServerCredentials::~ServerCredentials() {
  grpc_server_credentials_release(creds_);
}

grpc_server_credentials* ServerCredentials::GetRawCreds() { return creds_; }

std::shared_ptr<ServerCredentials> ServerCredentialsFactory::SslCredentials(
    const SslServerCredentialsOptions& options) {
  grpc_server_credentials* c_creds = grpc_ssl_server_credentials_create(
      reinterpret_cast<const unsigned char*>(options.pem_root_certs.c_str()),
      options.pem_root_certs.size(),
      reinterpret_cast<const unsigned char*>(options.pem_private_key.c_str()),
      options.pem_private_key.size(),
      reinterpret_cast<const unsigned char*>(options.pem_cert_chain.c_str()),
      options.pem_cert_chain.size());
  return std::shared_ptr<ServerCredentials>(new ServerCredentials(c_creds));
}

}  // namespace grpc