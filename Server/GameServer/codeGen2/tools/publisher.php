<?php

define('PATH_SOURCE', "./src/");
define('PATH_DESTINATION', "./dest/");

$update_files = array();

// �����ļ�
function copyFile($node) {
	global $update_files;
	
	$attrs = $node->attributes();
	
	$url = (String)$attrs["url"];
	$md5 = (String)$attrs["md5"];		
			
	$src = PATH_SOURCE.$url;
	
	// �ļ�����
	if (!file_exists($src)) {
		return false;
	}

	// ����Ŀ¼
	$dir = substr($url, 0, strrpos($url, '/') + 1);
	
	$root = PATH_DESTINATION.$dir;
	if (!is_dir($root)) {
		if (!mkdir($root, 0777, true)) {
			return false;
		}
	}

	// ����MD5
	$new_md5 = md5_file($src);
	if ($new_md5 == false) {
		return false;
	}
	
	$ret = false;
	
	// ��չ��
	$ext = strrchr($src, '.');
	
	$url = $dir.$md5.$ext;
	
	if ($md5 !== $new_md5) {		
		// Ŀ��Ŀ¼
		$dest = $root.$new_md5.$ext;
	
		// ����
		copy($src, $dest);
		
		$md5 = $new_md5;
		$url = $dir.$md5.$ext;
		
		$update_files[$md5] = $url;
		
		$ret = true;
	}
					
	if ($node->attributes()->url) {
		$node->attributes()->url = $url;
	} else {
		$node->addAttribute("url", $url);
	}
	if ($node->attributes()->md5) {
		$node->attributes()->md5 = $md5;
	} else {
		$node->addAttribute("md5", $md5);
	}
	
	return $ret;
}

// У�鷢�����
function check() {	
	global $update_files;
	
	$ret = 0;
	
	foreach ($update_files as $key => $value) {
		$url = PATH_DESTINATION.$value;
		if (file_exists($url)) {
			// У��MD5
			$new_md5 = md5_file($url);
			if ($key !== $new_md5) {
				echo $url.": MD5 incompatible!\n";
				$ret++;
			}
		} else {
			echo $url.": Can not find file!\n";
			$ret++;
		}
	}
		
	return $ret;
}

// ����Դ����
function update($src) {
	$xml = simplexml_load_file($src);
	if ($xml == null) {
		echo("read file failed: ".$src."\n");
		return false;
	}
	
	foreach ($xml->children() as $node){
		if($node->getName() == "PNGLoader") {
			foreach ($node->children() as $urls) {			
				$attrs = $urls->attributes();
				
				$url = PATH_SOURCE.(String)$attrs["url"];
				$md5 = (String)$attrs["md5"];
				if (file_exists($url)) {
					// ����MD5
					$new_md5 = md5_file($url);
					if (($new_md5 == false) || ($md5 === $new_md5)) {
						continue;
					}
					// ����MD5
					if ($urls->attributes()->md5) {
						$urls->attributes()->md5 = $new_md5;
					} else {
						$urls->addAttribute("md5", $new_md5);
					}
				}
			}
		} else {
			$attrs = $node->attributes();

			$url = PATH_SOURCE.(String)$attrs["url"];
			$md5 = (String)$attrs["md5"];
			// �ļ�����
			if (file_exists($url)) {
				// ����MD5
				$new_md5 = md5_file($url);
				if (($new_md5 == false) || ($md5 === $new_md5)) {
					continue;
				}
				// ����MD5
				if ($node->attributes()->md5) {
					$node->attributes()->md5 = $new_md5;
				} else {
					$node->addAttribute("md5", $new_md5);
				}
			}
		}
	}
	
	$xml->asXML($src);
	
	return true;
}

// ִ�з���
function execute($src) {	
	$xml = simplexml_load_file($src);
	if ($xml == null) {
		echo("read file failed: ".$src."\n");
		return false;
	}
	
	foreach ($xml->children() as $node){
		if($node->getName() == "PNGLoader") {
			foreach ($node->children() as $urls) {
				copyFile($urls);
			}
		} else {
			copyFile($node);
		}
	}
	
	$xml->asXML(PATH_DESTINATION."xml/data.xml");
	
	return true;
}

echo "please wait...\n";
// ִ�з���
execute(PATH_SOURCE."xml/data.xml");
// У��
$err = check();
if ($err === 0) {
	// ����Դ����
	update(PATH_SOURCE."xml/data.xml");
	// ��ӡ�����ļ�����
	echo count($update_files)." files updated!\n";
} else {
	// ��ӡ�������
	echo $err." errors occurred!\n";
}
echo "DONE";
?>