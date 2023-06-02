#!/usr/bin/env bash

if [[ $EUID -ne 0 ]]; then
        echo "ghidra-install.sh requires root privileges. Run with sudo."
        exit 1
fi

URL="https://github.com/NationalSecurityAgency/"\
"ghidra/releases/download/Ghidra_10.3_build/"\
"ghidra_10.3_PUBLIC_20230510.zip"

EXPECTED_CHECKSUM='4e990af9b22be562769bb6ce5d4d609fbb45455a7a2f756167b8cdcdb75887fc'
INSTALL_DIR=/usr/bin

# update pkg repos
echo Installing Ghidra dependencies...
apt-get update > /dev/null

if [[ $? -ne 0 ]]; then
        exit 1
fi

# install dependencies
apt-get install -y curl openjdk-17-jdk > /dev/null

if [[ $? -ne 0 ]]; then
	exit 1
fi

# download latest ghidra release (v10.3)
tmp_zip=$(mktemp)
echo Downloading Ghidra v10.3 artifacts from GitHub...
curl -L -s -o "${tmp_zip}" "${URL}"

if [[ $? -ne 0 ]]; then
	echo -e "\033[1;31mGhidra artifacts download failed!\033[0m"
	exit 1
fi

# verify checksum (SHA-256)
echo Computing SHA-256 checksum of payload...
computed_checksum=$(shasum -a 256 "${tmp_zip}" | awk '{print $1}')

if [[ "${computed_checksum}" != "${EXPECTED_CHECKSUM}" ]]; then
	echo -e "\033[1;31mSHA-256 checksum does not match!\033[0m"
	echo -e "Computed: ${computed_checksum}\nExpected: ${EXPECTED_CHECKSUM}"
	rm "${tmp_zip}"
	exit 1
fi

echo -e "\033[1;32mSHA-256 checksum verified!\033[0m"

# extract zip file
echo Extracting artifacts from zip file...
unzip -q -d "${INSTALL_DIR}" "${tmp_zip}"

if [[ $? -ne 0 ]]; then
        echo -e "\033[1;31mArtifact extraction failed!\033[0m"
	rm "${tmp_zip}"
        exit 1
fi

rm "${tmp_zip}"

# create symbolic link
echo "Creating symlink to Ghidra's launch script..."
ln -s "${INSTALL_DIR}/ghidra_10.3_PUBLIC/ghidraRun" "${INSTALL_DIR}/ghidra"

if [[ $? -eq 0 ]]; then
	echo -e "\033[1;32mSuccess! Run 'ghidra' in terminal to launch\033[0m"
else
	echo -e "\033[1;31mFailed to create 'ghidra' symlink\033[0m" 
fi
